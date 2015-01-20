#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

#include "Config.h"

using std::string;

class Options
{
public:

    int setConfigFilePath(string filePath);
    string getConfigFilePath();

    int setRasIp(string ip);
    string getRasIp();

    int setRasPort(uint16_t port);
    uint16_t getRasPort();

    int setRole(int role);
    int getRole();

    int setDbUserName(string username);
    string getDbUserName();

    int setDbPasswd(string passwd);
    string getDbPasswd();

    int setDbInstance(string instance);
    string getDbInstance();

    int setCliPort(uint16_t port);
    uint16_t getCliPort();

    int setDCPort(uint16_t port);
    uint16_t getDCPort();

private:

    string _configFilePath;
    string _rasIp;
    uint16_t _rasPort;
    int _role;
    string _dbUserName;
    string _dbPasswd;
    string _dbInstance;
    uint16_t _cliPort;
    uint16_t _dcPort;
};

#endif