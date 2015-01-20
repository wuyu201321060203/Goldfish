#include "ResManager.h"

ResManager::ResManager(ResGetStrategy* strategy):_resGetStrategy(strategy)
{}

void ResManager::applyResource(MessagePtr const& msg,
                               TcpConnectionPtr const& cliConn)
{

}

void ResManager::revokeResource(MessagePtr const& msg,
                                TcpConnectionPtr const& cliConn)
{

}

ResGetStrategyPtr ResManager::getStrategy()
{
    return _resGetStrategy;
}