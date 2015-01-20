#ifndef RESGETSTRATEGY_H
#define RESGETSTRATEGY_H

class ResGetStrategy
{
public:

    virtual void applyResource(MessagePtr const& msg,
                               TcpConnectionPtr const& cliConn);
    virtual void revokeResource(MessagePtr const& msg,
                                TcpConnectionPtr const& cliConn);
};

#endif