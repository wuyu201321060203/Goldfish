#ifndef POORMANAGER_H
#define POORMANAGER_H

#include "ResManager.h"

class PoorManager : public ResManager
{
public:

    PoorManager(ResGetStrategy* strategy);
    virtual void applyResource(MessagePtr const& msg,
                               TcpConnectionPtr const& cliConn);
    virtual void revokeResource(MessagePtr const& msg,
                                TcpConnectionPtr const& cliConn);
};

#endif