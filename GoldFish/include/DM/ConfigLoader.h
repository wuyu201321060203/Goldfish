#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>

#include "Config.h"
#include "Options.h"

class ConfigLoader
{
public:

    int setConfigFilePath(std::string);
    int loadConfig(Options&);

private:

    std::string _configFilePath;
};

#endif