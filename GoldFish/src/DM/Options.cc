#include <DM/Options.h>

int Options::setConfigFilePath(string filePath)
{
    _configFilePath = filePath;
    return RET_SUCCESS;
}

string Options::getConfigFilePath()
{
    return _configFilePath;
}

int Options::setRasIp(string ip)
{
    _rasIp = ip;
    return RET_SUCCESS;
}

string Options::getRasIp()
{
    return _rasIp;
}

int Options::setRasPort(uint16_t port)
{
    _rasPort = port;
    return RET_SUCCESS;
}

uint16_t Options::getRasPort()
{
    return _rasPort;
}

int Options::setRole(int role)
{
    _role = role;
    return RET_SUCCESS;
}

int Options::getRole()
{
    return _role;
}

int Options::setDbUserName(string username)
{
    _dbUserName = username;
    return RET_SUCCESS;
}

string Options::getDbUserName()
{
    return _dbUserName;
}

int Options::setDbPasswd(string passwd)
{
    _dbPasswd = passwd;
    return RET_SUCCESS;
}

string Options::getDbPasswd()
{
    return _dbPasswd;
}

int Options::setDbInstance(string instance)
{
    _dbInstance = instance;
    return RET_SUCCESS;
}

string Options::getDbInstance()
{
    return _dbInstance;
}

int Options::setCliPort(uint16_t port)
{
    _cliPort = port;
    return RET_SUCCESS;
}

uint16_t Options::getCliPort()
{
    return _cliPort;
}

int Options::setDCPort(uint16_t port)
{
    _dcPort = port;
    return RET_SUCCESS;
}

uint16_t Options::getDCPort()
{
    return _dcPort;
}