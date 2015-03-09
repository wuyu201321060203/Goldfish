/*
 *  The Config Loader class
 */

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include "Config.h"

class Options;

class ConfigLoader
{
public:

    int setConfigFilePath(STDSTR);
    int loadConfig(Options&);

private:

    STDSTR _configFilePath;
};

#endif