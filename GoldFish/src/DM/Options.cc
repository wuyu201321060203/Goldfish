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

int Options::setRole(int role)
{
    _role = role;
    return RET_SUCCESS;
}

int Options::getRole()
{
    return _role;
}