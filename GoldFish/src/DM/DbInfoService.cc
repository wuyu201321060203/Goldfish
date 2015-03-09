#include <string>

#include <boost/tokenizer.hpp>
#include <boost/weak_ptr.hpp>

#include <DM/DbInfoService.h>
#include <DM/Token.h>
#include <DM/util.h>
#include <DM/Initializer.h>
#include <DM/DMServer.h>

#include <muduo/base/Timestamp.h>
#ifdef DMDEBUG
#include <muduo/base/Logging.h>
#endif

using namespace muduo;
using namespace muduo::net;

#ifdef TEST

extern std::map<muduo::string , DomainDbInfoGetMsg> testDbMap;
extern std::map<muduo::string , DomainDbInfoGetACK> testDbMap1;
extern std::string timeDb1;

static void testDbSend(TcpConnectionPtr const& conn , DomainDbInfoGetMsg const& msg)
{
    testDbMap[conn->name()] = msg;
}

static void testDbSend1(TcpConnectionPtr const& conn , DomainDbInfoGetACK const& msg)
{
    testDbMap1[conn->name()] = msg;
}

#endif

DbInfoService::DbInfoService(DMServer* dm):CrossDomainInfoService(dm)
{
    ( Initializer::getDispatcher() ).registerMessageCallback(
        CrossDbInfoGetMsg::descriptor(),
        boost::bind(&CrossDomainInfoService::onCrossDomainInfoQuery,
        this , _1 , _2 , _3)
        );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        DomainDbInfoGetACK::descriptor(),
        boost::bind(&CrossDomainInfoService::onCrossDomainInfoReplyFromDC,
        this , _1 , _2 , _3)
        );
}

void DbInfoService::onCrossDomainInfoQuery(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           Timestamp timeStamp)
{
    CrossDbInfoGetMsgPtr query =  muduo::down_pointer_cast<CrossDbInfoGetMsg>(msg);
    std::string fakeToken = query->token();
#ifndef TEST
    ( Initializer::getDesEcbAcceptor() )->decode(fakeToken);
#endif
    Token token(fakeToken);
    CrossDbInfoGetACK reply;
    if(token.niuXThanDomainAdmin())
    {
        if(!_dcVec.empty())
        {
            Timestamp now = Timestamp::now();
            TcpConnectionWeakPtr cliConn(conn);
            muduo::string time( now.toString() );
            _cliMap.insert(Time2ConnMap::value_type(time , cliConn));//because
            //cross-domain information acquirement is a distributed task, so we
            //need to take measures to identify a reply from DC belong to which
            //client. We attach a timestamp with a client connection and relay
            //the cross-domain information query with the same timestamp, so
            //when a reply from DC arrives DM, through checking the timestamp in
            //the reply, DM will know this reply belongs to which client.
            DomainDbInfoGetMsg relayMsg;
            std::string tmp( MuduoStr2StdStr(time) );
#ifdef TEST
            timeDb1 = tmp;
#endif
            relayMsg.set_timestamp(tmp);
            _dcVec.erase( remove_if( _dcVec.begin() , _dcVec.end() , HelperFunctor() ),
                                    _dcVec.end() );//erase the DC connections which
            //are disconnected to DM , a garbage collection method.
            for(TcpConnectionWeakPtr dcConn : _dcVec)
            {
#ifndef TEST
                ( Initializer::getCodec() ).send(dcConn.lock() , relayMsg);//Oops!
#else
                testDbSend(dcConn.lock() , relayMsg);
#endif
            }

            return;
        }
        else
            reply.set_statuscode(SUCCESS);
    }
    else
        reply.set_statuscode(PERMISSION_DENIED);
    ( Initializer::getCodec() ).send(conn , reply);
}

void DbInfoService::onCrossDomainInfoReplyFromDC(TcpConnectionPtr const& conn,
                                                 MessagePtr const& msg,
                                                 Timestamp timeStamp)
{
    (_dm->_dcManager).resetTimerTask(conn);
    DomainDbInfoGetACKPtr dcACK = muduo::down_pointer_cast<DomainDbInfoGetACK>(msg);
    for(Time2ConnMap::iterator iter = _cliMap.begin() ; iter != _cliMap.end();)
    {
        TcpConnectionPtr temp( ( iter->second ).lock() );
        if(!temp)
            _cliMap.erase(iter++);
        else
            ++iter;
    }//erase client connections which are disconnected to DM at the time in order
    //to prevent _cliMap increasing all the time
    STDSTR time = dcACK->timestamp();
    muduo::string tmp( StdStr2MuduoStr(time) );
    Time2ConnMap::iterator iter = _cliMap.find(tmp);
    if(iter != _cliMap.end())
    {
        TcpConnectionPtr tmp( (iter->second).lock() );
        if(tmp)
#ifndef TEST
            ( Initializer::getCodec() ).send(tmp , *dcACK);
#else
            testDbSend1(tmp , *dcACK);
#endif
        else
            _cliMap.erase(iter);
    }
    else
    {
#ifdef DMDEBUG
        LOG_INFO << "timestamp is unknown , there is not a corresponding client";
#endif
    }
}

#ifdef TEST
typedef std::map<muduo::string , TcpConnectionWeakPtr> Time2ConnMap;
Time2ConnMap& DbInfoService::getCliMap()
{
    return _cliMap;
}
#endif