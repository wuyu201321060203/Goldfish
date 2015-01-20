#include "SysInfoService.h"

namespace
{
    class HelperFuntor
    {
    public:

        bool operator()(TcpConnectionWeakPtr conn)
        {
            TcpConnectionPtr tmp(conn->lock);
            return tmp ? true : false;
        }
    };
}

void SysInfoService::onSysInfoQuery(TcpConnectionPtr const& conn,
                                    SysInfoMsgPtr const& msg,
                                    muduo::Timestamp timeStamp)//decorate TODO
{
    boost::shared_ptr<Client2DMSysInfoQueryMsg> query =
        muduo::down_pointer_cast<Client2DMSysInfoQueryMsg>(msg);
    string token = query->token();
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep("\r\n");
    tokenizer tokens(token, sep);
    tokenizer::iterator tok_iter = tokens.begin();
    SysInfoQueryAck replyMsg;
    if(isRoot(*tok_iter))
    {
        _func(_dcVec);
        if(!_dcVec.empty())
        {
            Timestamp now = Timestamp::now();
            TcpConnectionWeakPtr connection(conn);
            _cliMap.insert(Time2ConnMap::value_type(now , connection));
            DM2DCDbSysQueryMsg newMsg;
            newMsg.set_timestamp(now);
            _dcVec.erase(remove_if(_dcVec.begin() , _dcVec.end() , HelperFuntor()));
            for(TcpConnectionWeakPtr dcConn : _dcVec)
                dcConn->send(newMsg);
            return;
        }
        else
            replyMsg.set_statusCode(SUCCESS);
    }
    else
        replyMsg.set_statusCode(AUTHFAILED);
    conn->send(replyMsg);
}

void SysInfoService::onSysInfoReplyFromDC(TcpConnectionPtr const& conn,
                                          SysInfoReplyPtr const& msg,
                                          muduo::Timestamp timeStamp)
{
    boost::shared_ptr<SysInfoQueryACK> Ack =
        muduo::down_pointer_cast<SysInfoQueryACK>(msg);
    Timestamp time = Ack->timestamp();
    Time2ConnMap::iterator iter = _cliMap.find(time);
    if(iter != _cliMap.end())
    {
        TcpConnectionPtr tmp(iter->second->lock());
        if(tmp)
            tmp->send(Ack);
        else
            _cliMap.erase(iter);
    }
    else
        LOG_INFO << "timestamp is unknown , there is not a corresponding user";
}