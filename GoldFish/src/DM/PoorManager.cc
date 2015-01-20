#include "PoorManager.h"

PoorManager::PoorManager(ResGetStrategy* strategy):_resGetStrategy(strategy)
{
}

void PoorManager::applyResource(MessagePtr const& msg,
                                TcpConnectionPtr const& cliConn)
{

}

void PoorManager::revokeResource(MessagePtr const& msg,
                                 TcpConnectionPtr const& cliConn)
{

}