#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

#include <boost/weak_ptr.hpp>

#include <muduo/net/TcpConnection.h>

#include <google/protobuf/message.h>

#include <protocol/MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_DESCRIPTION_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_DESCRIPTION_UPDATE.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_DESCRIPTION_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_DESCRIPTION_UPDATE.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_INFO_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_INFO_UPDATE.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_LOG_IN.pb.h>
#include <protocol/MSG_DC_DM_CONFIG_DELETE.pb.h>
#include <protocol/MSG_DC_DM_CONFIG_LOOKUP.pb.h>
#include <protocol/MSG_DC_DM_CONFIG_PERSISTENCE.pb.h>
#include <protocol/MSG_DC_DM_PING.pb.h>
#include <protocol/MSG_DC_DM_TOKEN_IDENTIFY.pb.h>
#include <protocol/MSG_DM_DC_DOMAIN_DBINFO_GET.pb.h>
#include <protocol/MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.h>
#include <protocol/FwmRcProtocol.pb.h>
#include <protocol/MSG_DC_DM_REGISTER.pb.h>

typedef boost::weak_ptr<muduo::net::TcpConnection> TcpConnectionWeakPtr;
typedef std::vector<TcpConnectionWeakPtr> TcpConnectionWeakPtrVec;
typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;

#define MODULE_NAME "DM"

/*log roll size*/
#define ROLL_SIZE 500000000

/*The domain id which root belongs to*/
#define ROOT_DOMAIN 88

/*The group which root and domain-admin belong to*/
#define ROOT_DOMAINADMIN_GROUP 88

/*DM config file path*/
#define CONFIG_FILE_PATH "/home/wuyu/Goldfish/GoldFish/src/DM/DMConfig.lua"

/* The macro for most used return value */
#define RET_SUCCESS 0
#define RET_FAIL -1

/* Database URL */

#define DB_URL "mysql://root:123@localhost:3306/DM"

/* The default number of threads */
#define DEFAULT_THREADS 3

/* The num of items of token*/
#define TOKEN_ITEM_NUM 5

typedef std::string STDSTR;
typedef unsigned long ulong;

typedef enum Role
{
    Master = 0,
    Slave
}Role;

#define EMPTYSTR ""

//encode/decode service macros
#define DES_KEY "01234567899876543210"//must shorter than 24
#define LEN_OF_KEY 24
#define ENCODE 0
#define DECODE 1

/* Table of error code*/
#define SUCCESS 0
#define UNKNOWN_TOKEN -1
#define PERMISSION_DENIED -2
#define EXISTED_DOMAIN -3
#define EXISTED_GROUP -4
#define BAD_CPU_REQUEST -5
#define BAD_MEM_REQUEST -6
#define BAD_EXEFILE_PATH -7
#define UNEXISTED_DOMAIN -8
#define UNEXISTED_GROUP -9
#define EXISTED_USER -10
#define BAD_USER_AUTHORITY_SET -11
#define UNKNOWN_SYSERROR -12
#define TOKEN_AUTH_FAIL -13
#define CRUSHED_DC -14//TODO
#define BAD_SQLQUERY -15
#define UNEXISTED_DBITEM -16
#define SQL_ERROR -17
#define UNEXISTED_RA -18
#define READ_DB_ERROR -19
#define FAILED_IMPORT -20
#define RLIMIT -21
#define INDEX_LOAD_FAIL -22
#define CONFIG_QUERY_FAIL -28
#define CONFIG_PRESERVE_FAIL -29
#define UNEXISTED_USER -30
#define DOMAIN_NO_CONFIG -31
#define CONFIG_DELETE_FAIL -32
#define USER_NOT_LOGIN -33
#define RESOURCE_APPLY_FAIL -34
#define RESOURCE_REVOKE_FAIL -35

//RAS cmd macros
#define MSG_FWM_RC_REGISTER 0x501
#define MSG_FWM_RC_REGISTER_ACK 0x502
#define MSG_FWM_RC_REQUEST_START_SLAVE 0x503
#define MSG_FWM_RC_REQUEST_START_SLAVE_ACK 0x504
#define MSG_FWM_RC_STOP_MODULE 0x509
#define MSG_FWM_RC_STOP_MODULE_ACK 0x510
#define MSG_FWM_RC_SEND_HEARTBEAT 0x513
#define MSG_FWM_RC_SEND_HEARTBEAT_ACK 0x514

/*
 * protocol macro
 */

typedef MSG_CLIENT_DM_DOMAIN_CREATE DomainCreateMsg;
typedef boost::shared_ptr<DomainCreateMsg> DomainCreateMsgPtr;

typedef MSG_DM_CLIENT_DOMAIN_CREATE_ACK DomainCreateACK;
typedef boost::shared_ptr<DomainCreateACK> DomainCreateACKPtr;

typedef MSG_CLIENT_DM_GROUP_CREATE GroupCreateMsg;
typedef boost::shared_ptr<GroupCreateMsg> GroupCreateMsgPtr;

typedef MSG_DM_CLIENT_GROUP_CREATE_ACK GroupCreateACK;
typedef boost::shared_ptr<GroupCreateACK>  GroupCreateACKPtr;

typedef MSG_CLIENT_DM_DOMAIN_DESTROY DomainDestroyMsg;
typedef boost::shared_ptr<DomainDestroyMsg> DomainDestroyMsgPtr;

typedef MSG_DM_CLIENT_DOMAIN_DESTROY_ACK DomainDestroyACK;
typedef boost::shared_ptr<DomainDestroyACK> DomainDestroyACKPtr;

typedef MSG_CLIENT_DM_GROUP_DESTROY GroupDestroyMsg;
typedef boost::shared_ptr<GroupDestroyMsg> GroupDestroyMsgPtr;

typedef MSG_DM_CLIENT_GROUP_DESTROY_ACK GroupDestroyACK;
typedef boost::shared_ptr<GroupDestroyACK> GroupDestroyACKPtr;

typedef MSG_CLIENT_DM_DOMAIN_DESCRIPTION_UPDATE DomainInfoUpdateMsg;
typedef boost::shared_ptr<DomainInfoUpdateMsg> DomainInfoUpdateMsgPtr;

typedef MSG_DM_CLIENT_DOMAIN_DESCRIPTION_UPDATE_ACK DomainInfoUpdateACK;
typedef boost::shared_ptr<DomainInfoUpdateACK> DomainInfoUpdateACKPtr;

typedef MSG_CLIENT_DM_GROUP_DESCRIPTION_UPDATE GroupInfoUpdateMsg;
typedef boost::shared_ptr<GroupInfoUpdateMsg> GroupInfoUpdateMsgPtr;

typedef MSG_DM_CLIENT_GROUP_DESCRIPTION_UPDATE_ACK GroupInfoUpdateACK;
typedef boost::shared_ptr<GroupInfoUpdateACK> GroupInfoUpdateACKPtr;

typedef MSG_CLIENT_DM_DOMAIN_DESCRIPTION_GET DomainInfoGetMsg;
typedef boost::shared_ptr<DomainInfoGetMsg> DomainInfoGetMsgPtr;

typedef MSG_DM_CLIENT_DOMAIN_DESCRIPTION_GET_ACK DomainInfoGetACK;
typedef boost::shared_ptr<DomainInfoGetACK> DomainInfoACKPtr;

typedef MSG_CLIENT_DM_GROUP_DESCRIPTION_GET GroupInfoGetMsg;
typedef boost::shared_ptr<GroupInfoGetMsg> GroupInfoGetMsgPtr;

typedef MSG_DM_CLIENT_GROUP_DESCRIPTION_GET_ACK GroupInfoGetACK;
typedef boost::shared_ptr<GroupInfoGetACK> GroupInfoGetACKPtr;

typedef MSG_CLIENT_DM_CROSS_DBINFO_GET CrossDbInfoGetMsg;
typedef boost::shared_ptr<CrossDbInfoGetMsg> CrossDbInfoGetMsgPtr;

typedef MSG_DM_CLIENT_CROSS_DBINFO_GET_ACK CrossDbInfoGetACK;
typedef boost::shared_ptr<CrossDbInfoGetACK> CrossDbInfoGetACKPtr;

typedef MSG_CLIENT_DM_CROSS_SYSINFO_GET CrossSysInfoGetMsg;
typedef boost::shared_ptr<CrossSysInfoGetMsg> CrossSysInfoGetMsgPtr;

typedef MSG_DM_CLIENT_CROSS_SYSINFO_GET_ACK CrossSysInfoGetACK;
typedef boost::shared_ptr<CrossSysInfoGetACK> CrossSysInfoGetACKPtr;

typedef MSG_CLIENT_DM_USER_CREATE UserCreateMsg;
typedef boost::shared_ptr<UserCreateMsg> UserCreateMsgPtr;

typedef MSG_DM_CLIENT_USER_CREATE_ACK UserCreateACK;
typedef boost::shared_ptr<UserCreateACK> UserCreateACKPtr;

typedef MSG_CLIENT_DM_USER_DESTROY UserDestroyMsg;
typedef boost::shared_ptr<UserDestroyMsg> UserDestroyMsgPtr;

typedef MSG_DM_CLIENT_USER_DESTROY_ACK UserDestroyACK;
typedef boost::shared_ptr<UserDestroyACK> UserDestroyACKPtr;

typedef MSG_CLIENT_DM_USER_INFO_UPDATE UserInfoUpdateMsg;
typedef boost::shared_ptr<UserInfoUpdateMsg> UserInfoUpdateMsgPtr;

typedef MSG_DM_CLIENT_USER_INFO_UPDATE_ACK UserInfoUpdateACK;
typedef boost::shared_ptr<UserInfoUpdateACK> UserInfoUpdateACKPtr;

typedef MSG_CLIENT_DM_USER_INFO_GET UserInfoGetMsg;
typedef boost::shared_ptr<UserInfoGetMsg> UserInfoGetMsgPtr;

typedef MSG_DM_CLIENT_USER_INFO_GET_ACK UserInfoGetACK;
typedef boost::shared_ptr<UserInfoGetACK> UserInfoGetACKPtr;

typedef MSG_CLIENT_DM_USER_LOG_IN UserLoginMsg;
typedef boost::shared_ptr<UserLoginMsg> UserLoginMsgPtr;

typedef MSG_DM_CLIENT_USER_LOG_IN_ACK UserLoginACK;
typedef boost::shared_ptr<UserLoginACK> UserLoginACKPtr;

typedef MSG_DC_DM_TOKEN_IDENTIFY TokenIdentifyMsg;
typedef boost::shared_ptr<TokenIdentifyMsg> TokenIdentifyMsgPtr;

typedef MSG_DM_DC_TOKEN_IDENTIFY_ACK TokenIdentifyACK;
typedef boost::shared_ptr<TokenIdentifyACK> TokenIdentifyACKPtr;

typedef MSG_DM_DC_DOMAIN_SYSINFO_GET DomainSysInfoGetMsg;
typedef boost::shared_ptr<DomainSysInfoGetMsg> DomainSysInfoGetMsgPtr;

typedef MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK DomainSysInfoGetACK;
typedef boost::shared_ptr<DomainSysInfoGetACK> DomainSysInfoGetACKPtr;

typedef MSG_DM_DC_DOMAIN_DBINFO_GET DomainDbInfoGetMsg;
typedef boost::shared_ptr<DomainDbInfoGetMsg> DomainDbInfoGetMsgPtr;

typedef MSG_DC_DM_DOMAIN_DBINFO_GET_ACK DomainDbInfoGetACK;
typedef boost::shared_ptr<DomainDbInfoGetACK> DomainDbInfoGetACKPtr;

typedef MSG_DC_DM_CONFIG_PERSISTENCE ConfigPersistenceMsg;
typedef boost::shared_ptr<ConfigPersistenceMsg> ConfigPersistenceMsgPtr;

typedef MSG_DM_DC_CONFIG_PERSISTENCE_ACK ConfigPersistenceACK;
typedef boost::shared_ptr<ConfigPersistenceACK> ConfigPersistenceACKPtr;

typedef MSG_DC_DM_CONFIG_LOOKUP ConfigLookupMsg;
typedef boost::shared_ptr<ConfigLookupMsg> ConfigLookupMsgPtr;

typedef MSG_DM_DC_CONFIG_LOOKUP_ACK ConfigLookupACK;
typedef boost::shared_ptr<ConfigLookupACK> ConfigLookupACKPtr;

typedef MSG_DC_DM_CONFIG_DELETE ConfigDeleteMsg;
typedef boost::shared_ptr<ConfigDeleteMsg> ConfigDeleteMsgPtr;

typedef MSG_DM_DC_CONFIG_DELETE_ACK ConfigDeleteACK;
typedef boost::shared_ptr<ConfigDeleteACK> ConfigDeleteACKPtr;

typedef MSG_DC_DM_PING PingMsg;
typedef boost::shared_ptr<PingMsg> PingMsgPtr;

typedef MSG_DM_DC_PONG PongMsg;
typedef boost::shared_ptr<PongMsg> PongMsgPtr;

typedef MSG_DC_DM_REGISTER RegisterMsg;
typedef boost::shared_ptr<RegisterMsg> RegisterMsgPtr;

typedef MSG_DM_DC_REGISTER_ACK RegisterMsgACK;
typedef boost::shared_ptr<RegisterMsgACK> RegisterMsgACKPtr;

#endif