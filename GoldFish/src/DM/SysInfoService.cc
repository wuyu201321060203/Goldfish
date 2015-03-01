#include <string>

#include <boost/tokenizer.hpp>

#include <DM/SysInfoService.h>
#include <DM/Token.h>
#include <DM/util.h>
#include <DM/Initializer.h>

#include <muduo/base/Timestamp.h>
#include <muduo/base/Logging.h>

using namespace muduo::net;
using namespace muduo;

void SysInfoService::onCrossDomainInfoQuery(TcpConnectionPtr const& conn,
                                            MessagePtr const& msg,
                                            muduo::Timestamp timeStamp)//decorate TODO
{
    CrossSysInfoGetMsgPtr query =  muduo::down_pointer_cast<CrossSysInfoGetMsg>(msg);
    std::string fakeToken = query->token();
    ( Initializer::getDesEcbAcceptor() )->decode(fakeToken);
    Token token(fakeToken);
    CrossSysInfoGetACK reply;
    if(token.niuXThanDomainAdmin())
    {
        _dcVec.clear();
        _func(_dcVec);
        if(!_dcVec.empty())
        {
            Timestamp now = Timestamp::now();
            TcpConnectionWeakPtr cliConn(conn);
            muduo::string time( now.toString() );
            _cliMap.insert(Time2ConnMap::value_type(time , cliConn));
            DomainSysInfoGetMsg relayMsg;
            std::string tmp( MuduoStr2StdStr(time) );
            relayMsg.set_timestamp(tmp);
            _dcVec.erase( remove_if( _dcVec.begin() , _dcVec.end() , HelperFunctor() ),
                          _dcVec.end() );
            for(TcpConnectionWeakPtr dcConn : _dcVec)
                ( Initializer::getCodec() ).send(dcConn.lock() , relayMsg);//Oops!
            return;
        }
        else
            reply.set_statuscode(SUCCESS);
    }
    else
        reply.set_statuscode(PERMISSION_DENIED);
    ( Initializer::getCodec() ).send(conn , reply);
}

void SysInfoService::onCrossDomainInfoReplyFromDC(TcpConnectionPtr const& conn,
                                                  MessagePtr const& msg,
                                                  muduo::Timestamp timeStamp)
{
    DomainSysInfoGetACKPtr dcACK = muduo::down_pointer_cast<DomainSysInfoGetACK>(msg);
    for(Time2ConnMap::iterator iter = _cliMap.begin() ; iter != _cliMap.end();)
    {
        TcpConnectionPtr temp( ( iter->second ).lock() );
        if(!temp)
            _cliMap.erase(iter++);
        else
            ++iter;
    }
    STDSTR time = dcACK->timestamp();
    muduo::string tmp( StdStr2MuduoStr(time) );
    Time2ConnMap::iterator iter = _cliMap.find(tmp);
    if(iter != _cliMap.end())
    {
        TcpConnectionPtr tmp( (iter->second).lock() );
        if(tmp)
            ( Initializer::getCodec() ).send(tmp , *dcACK);
        else
            _cliMap.erase(iter);
    }
    else
        LOG_INFO << "timestamp is unknown , there is not a corresponding client";
}