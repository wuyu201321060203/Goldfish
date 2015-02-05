#include <assert.h>
#include <stdint.h>

#include <DM/ConfigLoader.h>

#include "lua/fflua.h"

using namespace ff;
using namespace std;

int ConfigLoader::setConfigFilePath(string path)
{
    _configFilePath = path;
    return RET_SUCCESS;
}

int ConfigLoader::loadConfig(Options& options)
{
    fflua_t fflua;
    //fflua.add_package_path(_configFilePath);
    fflua.load_file(_configFilePath);
    int role;
    assert( 0 == fflua.get_global_variable("Role", role) );
    options.setRole(role);
    return RET_SUCCESS;
}