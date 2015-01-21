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
    string rip;
    uint16_t rport;
    int role;
    string username;
    string passwd;
    string instance;
    uint16_t cport;
    uint16_t dport;
    assert( 0 == fflua.get_global_variable("RAS_IP", rip) );
    assert( 0 == fflua.get_global_variable("RAS_Port", rport) );
    assert( 0 == fflua.get_global_variable("Role", role) );
    assert( 0 == fflua.get_global_variable("Client_Port", cport) );
    assert( 0 == fflua.get_global_variable("DC_Port", dport) );
    options.setRasIp(rip);
    options.setRasPort(rport);
    options.setRole(role);
    options.setCliPort(cport);
    options.setDCPort(dport);
    return RET_SUCCESS;
}