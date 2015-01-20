#ifndef RESMANAGER_H
#define RESMANAGER_H

class ResManager
{
public:

    ResManager(ResGetStrategy*);
    virtual void applyResource(MessagePtr const& msg,
                               TcpConnectionPtr const& cliConn);
    virtual void revokeResource(MessagePtr const& msg,
                                TcpConnectionPtr const& cliConn);

    ResGetStrategyPtr getStrategy();

private:

    ResGetStrategyPtr _resGetStrategy;
};

#endif