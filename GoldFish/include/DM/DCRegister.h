/*
 * DCRegister is used to manage registration of DCs
 */

#ifndef DCREGISTER_H
#define DCREGISTER_H

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include <DM/Config.h>

class DMServer;

class DCRegister
{
public:

    DCRegister(DMServer*);

    /*
     * name : onMessage
     *
     * description : the callback function which is called when a DC want to
     * register to DM
     *
     * @conn: the connection of DC
     * @msg : the request for registering to DM
     * @receiveTime : the receive time of a request
     */
    void onMessage(muduo::net::TcpConnectionPtr const& conn,
                   MessagePtr const& msg,
                   muduo::Timestamp receiveTime);

private:

    /*
     * name : doRegister
     *
     * description : the execute function which real registers to DM. It is called
     *               by onMessage.
     *
     * @conn : the connection of DC
     * @moduleID : the id of a DC which is allocated by RAS
     * @ip   : the ip of DC
     * @port : the client service port of a DC
     */
    void doRegister(muduo::net::TcpConnectionPtr const& conn,
                    uint32_t moduleID , STDSTR ip , uint32_t port);

private:

    DMServer* _dm;
};

#endif