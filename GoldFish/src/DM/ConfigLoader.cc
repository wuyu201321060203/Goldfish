#include <assert.h>
#include <stdint.h>

#include <DM/ConfigLoader.h>
#include <DM/Options.h>

#include <fflua.h>

using namespace ff;
using namespace std;

int ConfigLoader::setConfigFilePath(string path)
{
    _configFilePath = path;
    return RET_SUCCESS;
}

/*
 * name : loadConfig
 *
 * description : load the content from the file in CONFIG_FILE_PATH which
 *               is written in lua. Although it is not much use now, but later
 *               extension is very convenient.
 *
 * @options : the options which belong to DM.
 *
 * @return : 0(RET_SUCCESS)
 *
 */
int ConfigLoader::loadConfig(Options& options)
{
    fflua_t fflua;
    fflua.load_file(_configFilePath);
    int role;
    assert( 0 == fflua.get_global_variable("Role", role) );
    options.setRole(role);
    return RET_SUCCESS;
}