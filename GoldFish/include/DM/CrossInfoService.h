/*
 * The template version of CrossDomainInfoService class and
 * now it is not used.
 */

#ifndef CROSSINFOSERVICE_H
#define CROSSINFOSERVICE_H

#include <vector>
#include <map>
#include <string>

#include <boost/function.hpp>
#include <boost/tokenizer.hpp>

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/Types.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/Logging.h>

#include "Config.h"
#include "Token.h"
#include "util.h"
#include "Initializer.h"

using muduo::net::TcpConnectionPtr;
using muduo::Timestamp;

extern Initializer g_Initializer;//TODO change to static
#ifdef TEST

extern std::map<muduo::string , DomainDbInfoGetMsg> testMap;
extern std::map<muduo::string , DomainDbInfoGetACK> testMap1;
extern std::string time1;

static void testSend(TcpConnectionPtr const& conn , DomainDbInfoGetMsg const& msg)
{
    testMap[conn->name()] = msg;
}

static void testSend1(TcpConnectionPtr const& conn , DomainDbInfoGetACK const& msg)
{
    testMap1[conn->name()] = msg;
}

#endif

template<typename T , typename U , typename R , typename Q>
class CrossInfoService
{
public:

    typedef std::vector<TcpConnectionWeakPtr> TcpConnectionWeakPtrVec;
    typedef boost::function<void (TcpConnectionWeakPtrVec&)> DCListGetFunc;
    typedef std::map<muduo::string , TcpConnectionWeakPtr> Time2ConnMap;

    void onCrossInfoQuery(TcpConnectionPtr const& conn,
                          MessagePtr const& msg,
                          Timestamp timeStamp)
    {
        boost::shared_ptr<T> query =  muduo::down_pointer_cast<T>(msg);
        std::string fakeToken = query->token();
        Token token(fakeToken);
        U reply;
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
                R relayMsg;
                std::string tmp( MuduoStr2StdStr(time) );
#ifdef TEST
                time1 = tmp;
#endif
                relayMsg.set_timestamp(tmp);
                _dcVec.erase(remove_if(_dcVec.begin() , _dcVec.end(),
                                HelperFunctor()) , _dcVec.end());

                for(TcpConnectionWeakPtr dcConn : _dcVec)
                {
#ifndef TEST
                    ( g_Initializer.getCodec() ).send(dcConn.lock() , relayMsg);//Oops!
#else
                    testSend(dcConn.lock() , relayMsg);
#endif
                }
                return;
            }
            else
                reply.set_statuscode(SUCCESS);
        }
        else
            reply.set_statuscode(PERMISSION_DENIED);
        ( g_Initializer.getCodec() ).send(conn , reply);
    }

    void onCrossInfoReplyFromDC(TcpConnectionPtr const& conn,
                                MessagePtr const& msg,
                                Timestamp timeStamp)
    {
        boost::shared_ptr<Q> dcACK = muduo::down_pointer_cast<Q>(msg);
        STDSTR time = dcACK->timestamp();
        muduo::string tmp( StdStr2MuduoStr(time) );
        Time2ConnMap::iterator iter = _cliMap.find(tmp);
        if(iter != _cliMap.end())
        {
            TcpConnectionPtr tmp( (iter->second).lock() );
            if(tmp)
#ifndef TEST
                ( g_Initializer.getCodec() ).send(tmp , *dcACK );
#else
                testSend1(tmp , *dcACK);
#endif
            else
                _cliMap.erase(iter);
        }
        else
            LOG_INFO << "timestamp is unknown , there is not a corresponding client";
    }

    int setGetDCListFunc(DCListGetFunc const& func)
    {
        _func = func;
        return RET_SUCCESS;
    }

#ifdef TEST
    Time2ConnMap& getCliMap()
    {
        return _cliMap;
    }
#endif

private:

    class HelperFunctor
    {
    public:

        bool operator()(TcpConnectionWeakPtr conn)
        {
            muduo::net::TcpConnectionPtr tmp( conn.lock() );
            return tmp ? false : true;
        }
    };

    TcpConnectionWeakPtrVec _dcVec;
    Time2ConnMap _cliMap;
    DCListGetFunc _func;
};

#endif