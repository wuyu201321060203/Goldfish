#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <boost/weak_ptr.hpp>
#include <muduo/net/TcpConnection.h>
#include <google/protobuf/message.h>

#include <protocol/MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_ADMIN_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_ADMIN_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_DESCRIPTION_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_DESCRIPTION_UPDATE.pb.h>
#include <protocol/MSG_CLIENT_DM_DOMAIN_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_ADMIN_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_ADMIN_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_DESCRIPTION_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_DESCRIPTION_UPDATE.pb.h>
#include <protocol/MSG_CLIENT_DM_GROUP_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_ROOT_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_ROOT_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_CREATE.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_DESTROY.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_INFO_GET.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_INFO_UPDATE.pb.h>
#include <protocol/MSG_CLIENT_DM_USER_LOG_IN.pb.h>
#include <protocol/MSG_DC_DM_CONFIG_DELETE.pb.h>
#include <protocol/MSG_DC_DM_CONFIG_LOOPUP.pb.h>
#include <protocol/MSG_DC_DM_CONFIG_PERSISTENCE.pb.h>
#include <protocol/MSG_DC_DM_PING.pb.h>
#include <protocol/MSG_DC_DM_TOKEN_IDENTIFY.pb.h>
#include <protocol/MSG_DM_DC_DOMAIN_DBINFO_GET.pb.h>
#include <protocol/MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.h>

typedef boost::weak_ptr<muduo::net::TcpConnection> TcpConnectionWeakPtr;
typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;

#define RET_SUCCESS 0
#define RET_FAIL -1

typedef enum Role
{
    Master = 0,
    Slave
}Role;

#define AUTHFAILED -2
#define LOAD_FAIL -28
#define PRESERVE_FAIL -29
#define DELETE_FAIL -32
#define TOKEN_AUTH_FAIL -13
#define USER_NOT_EXIST -10


#define DEFAULT_THREADS 3

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

typedef MSG_CLIENT_DM_DOMAIN_DESTORY DomainDestoryMsg;
typedef boost::shared_ptr<DomainDestoryMsg> DomainDestoryMsgPtr;

typedef MSG_DM_CLIENT_DOMAIN_DESTORY_ACK DomainDestroyACK;
typedef boost::shared_ptr<DomainDestroyACK> DomainDestoryACKPtr;

typedef MSG_CLIENT_DM_GROUP_DESTORY GroupDestoryMsg;
typedef boost::shared_ptr<GroupDestoryMsg> GroupDestoryMsgPtr;

typedef MSG_DM_CLIENT_GROUP_DESTORY_ACK GroupDestoryACK;
typedef boost::shared_ptr<GroupDestoryACK> GroupDestoryACKPtr;

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

typedef MSG_CLIENT_DM_GROUP_ADMIN_CREATE GroupAdminCreateMsg;
typedef boost::shared_ptr<GroupAdminCreateMsg> GroupAdminCreateMsgPtr;

typedef MSG_DM_CLIENT_GROUP_ADMIN_CREATE_ACK GroupAdminCreateACK;
typedef boost::shared_ptr<GroupAdminCreateACK> GroupAdminCreateACKPtr;

typedef MSG_CLIENT_DM_DOMAIN_ADMIN_CREATE DomainAdminCreateMsg;
typedef boost::shared_ptr<DomainAdminCreateMsg> DomainAdminCreateMsgPtr;

typedef MSG_DM_CLIENT_DOMAIN_ADMIN_CREATE_ACK DomainAdminCreateACK;
typedef boost::shared_ptr<DomainAdminCreateACK> DomainAdminCreateACKPtr;

typedef MSG_CLIENT_DM_ROOT_CREATE RootCreateMsg;
typedef boost::shared_ptr<RootCreateMsg> RootCreateMsgPtr;

typedef MSG_DM_CLIENT_ROOT_CREATE_ACK RootCreateACK;
typedef boost::shared_ptr<RootCreateMsg> RootCreateACKPtr;

typedef MSG_CLIENT_DM_USER_DESTORY UserDestoryMsg;
typedef boost::shared_ptr<UserDestoryMsg> UserDestoryMsgPtr;

typedef MSG_DM_CLIENT_USER_DESTORY_ACK UserDestoryACK;
typedef boost::shared_ptr<UserDestoryACK> UserDestoryACKPtr;

typedef MSG_CLIENT_DM_GROUP_ADMIN_DESTORY GroupAdminDestoryMsg;
typedef boost::shared_ptr<GroupAdminDestoryMsg> GroupAdminDestoryMsgPtr;

typedef MSG_DM_CLIENT_GROUP_ADMIN_DESTORY_ACK GroupAdminDestoryACK;
typedef boost::shared_ptr<GroupAdminDestoryACK> GroupAdminDestoryACKPtr;

typedef MSG_CLIENT_DM_DOMAIN_ADMIN_DESTORY DomainAdminDestoryMsg;
typedef boost::shared_ptr<DomainAdminDestoryMsg> DomainAdminDestoryMsgPtr;

typedef MSG_DM_CLIENT_DOMAIN_ADMIN_DESTORY_ACK DomainAdminDestoryACK;
typedef boost::shared_ptr<DomainAdminDestoryACK> DomainAdminDestoryACKPtr;

typedef MSG_CLIENT_DM_ROOT_DESTORY RootDestoryMsg;
typedef boost::shared_ptr<RootDestoryMsg> RootDestoryMsgPtr;

typedef MSG_DM_CLIENT_ROOT_DESTORY_ACK RootDestoryACK;
typedef boost::shared_ptr<RootDestoryACK> RootDestoryACKPtr;

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

/*
typedef MSG_DM_RSA_DOMAIN_RESOURCE_APPLY DomainResourceApplyMsg;
typedef boost::shared_ptr<DomainResourceApplyMsg> DomainResourceApplyMsgPtr;
*/
//ACK

/*
typedef MSG_DM_RSA_DOMAIN_RESOURCE_REVOKE DomainResourceRevokeMsg;
typedef boost::shared_ptr<DomainResourceRevokeMsg> DomainResourceRevokeMsgPtr;
*/
//ACK

typedef MSG_DC_DM_CONFIG_PERSISTENCE ConfigPersistenceMsg;
typedef boost::shared_ptr<ConfigPersistenceMsg> ConfigPersistenceMsgPtr;

typedef MSG_DM_DC_CONFIG_PERSISTENCE_ACK ConfigPersistenceACK;
typedef boost::shared_ptr<ConfigPersistenceACK> ConfigPersistenceACKPtr;

typedef MSG_DC_DM_CONFIG_LOOPUP ConfigLookupMsg;
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

#endif