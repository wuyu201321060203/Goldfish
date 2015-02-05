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

    int setRole(int role);
    int getRole();

private:

    string _configFilePath;
    int _role;
};

#endif