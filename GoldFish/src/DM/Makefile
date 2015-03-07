MUDUO_DIRECTORY = $(HOME)/build/debug-install
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
OOZDB_INCLUDE = ./OOzdb
LUA_INCLUDE = ./lua
DM_INCLUDE = $(HOME)/Goldfish/GoldFish/include
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = $(HOME)/gtest-1.7.0

# Where to find user code.
USER_DIR = .
DM_SRC_DIR = $(HOME)/Goldfish/GoldFish/src/DM
PROTO_SRC_DIR = $(HOME)/Goldfish/GoldFish/src/protocol

CXX = g++
LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net_cpp11 -lmuduo_base_cpp11 -lpthread -lrt\
		  -lmysqlclient -llua5.1 -ldl -lboost_program_options -lprotobuf -lcrypto

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -ggdb3 -Wall -Wextra -pthread -I$(MUDUO_INCLUDE) -I$(OOZDB_INCLUDE)\
			-I$(DM_INCLUDE) -I$(LUA_INCLUDE) -std=c++11 -DTEST

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = DM

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS)

clean :
	rm -f $(TESTS)
	rm *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

ConfigLoader.o : $(DM_SRC_DIR)/ConfigLoader.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Options.o : $(DM_SRC_DIR)/Options.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Initializer.o : $(DM_SRC_DIR)/Initializer.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ProtobufCodec.o : $(DM_SRC_DIR)/ProtobufCodec.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

DMServer.o : $(DM_SRC_DIR)/DMServer.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

RemoteDomainInfoService.o : $(DM_SRC_DIR)/RemoteDomainInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_CONFIG_PERSISTENCE.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_CONFIG_PERSISTENCE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_TOKEN_IDENTIFY.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_TOKEN_IDENTIFY.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_CONFIG_LOOKUP.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_CONFIG_LOOKUP.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_CONFIG_DELETE.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_CONFIG_DELETE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_GROUP_CREATE.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_GROUP_CREATE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_GROUP_DESCRIPTION_GET.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_GROUP_DESCRIPTION_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_GROUP_DESCRIPTION_UPDATE.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_GROUP_DESCRIPTION_UPDATE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_GROUP_DESTROY.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_GROUP_DESTROY.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_USER_CREATE.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_USER_CREATE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_USER_DESTROY.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_USER_DESTROY.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_USER_INFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_USER_INFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_USER_INFO_UPDATE.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_USER_INFO_UPDATE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_USER_LOG_IN.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_USER_LOG_IN.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_DOMAIN_CREATE.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_DOMAIN_CREATE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_DOMAIN_DESCRIPTION_GET.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_DOMAIN_DESCRIPTION_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_DOMAIN_DESCRIPTION_UPDATE.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_DOMAIN_DESCRIPTION_UPDATE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_DOMAIN_DESTROY.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_DOMAIN_DESTROY.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_REGISTER.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_REGISTER.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

FwmRcProtocol.pb.o : $(PROTO_SRC_DIR)/FwmRcProtocol.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DM_DC_DOMAIN_DBINFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_DM_DC_DOMAIN_DBINFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_PING.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_PING.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

DbAcceptor.o : $(DM_SRC_DIR)/DbAcceptor.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Token.o : $(DM_SRC_DIR)/Token.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

util.o : $(DM_SRC_DIR)/util.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

GroupInfoService.o : $(DM_SRC_DIR)/GroupInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

UserInfoService.o : $(DM_SRC_DIR)/UserInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ProtobufRASCodec.o : $(DM_SRC_DIR)/ProtobufRASCodec.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

UserManager.o : $(DM_SRC_DIR)/UserManager.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

DesEcbService.o : $(DM_SRC_DIR)/DesEcbService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

CryptographicService.o : $(DM_SRC_DIR)/CryptographicService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ResourceManager.o : $(DM_SRC_DIR)/ResourceManager.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

RASTunnel.o : $(DM_SRC_DIR)/RASTunnel.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

DCRegister.o : $(DM_SRC_DIR)/DCRegister.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

DbInfoService.o : $(DM_SRC_DIR)/DbInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

SysInfoService.o : $(DM_SRC_DIR)/SysInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

CrossDomainInfoService.o : $(DM_SRC_DIR)/CrossDomainInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

GenericInfoService.o : $(DM_SRC_DIR)/GenericInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

CustomizedServiceAcceptor.o : $(DM_SRC_DIR)/CustomizedServiceAcceptor.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

main.o : $(DM_SRC_DIR)/main.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

DM : ConfigLoader.o Options.o\
			  Initializer.o ProtobufCodec.o Connection.o ConnectionPool.o MemoryOperation.o MysqlConnection.o \
			  MysqlPreparedStatement.o MysqlResultSet.o PreparedStatement.o ResultSet.o \
			  StringBuffer.o StrOperation.o TimeOperation.o URL.o MSG_DC_DM_CONFIG_PERSISTENCE.pb.o\
			  DbAcceptor.o MSG_DC_DM_CONFIG_LOOKUP.pb.o MSG_DC_DM_CONFIG_DELETE.pb.o\
			  Token.o util.o \
		      MSG_DM_DC_DOMAIN_DBINFO_GET.pb.o MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.o\
			  MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.o MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.o\
			  MSG_CLIENT_DM_GROUP_CREATE.pb.o MSG_CLIENT_DM_GROUP_DESCRIPTION_GET.pb.o\
			  MSG_CLIENT_DM_GROUP_DESCRIPTION_UPDATE.pb.o MSG_CLIENT_DM_GROUP_DESTROY.pb.o\
			  GroupInfoService.o \
			  UserInfoService.o MSG_CLIENT_DM_USER_CREATE.pb.o MSG_CLIENT_DM_USER_DESTROY.pb.o\
			  MSG_CLIENT_DM_USER_INFO_GET.pb.o MSG_CLIENT_DM_USER_INFO_UPDATE.pb.o\
			  ProtobufRASCodec.o \
			  UserManager.o MSG_CLIENT_DM_USER_LOG_IN.pb.o \
			  CryptographicService.o DesEcbService.o\
			  ResourceManager.o RemoteDomainInfoService.o\
			  MSG_CLIENT_DM_DOMAIN_CREATE.pb.o MSG_CLIENT_DM_DOMAIN_DESCRIPTION_GET.pb.o\
			  MSG_CLIENT_DM_DOMAIN_DESCRIPTION_UPDATE.pb.o MSG_CLIENT_DM_DOMAIN_DESTROY.pb.o\
			  RASTunnel.o FwmRcProtocol.pb.o DCRegister.o\
			  MSG_DC_DM_REGISTER.pb.o MSG_DC_DM_TOKEN_IDENTIFY.pb.o\
			  DbInfoService.o SysInfoService.o DMServer.o MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.o\
			  MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.o MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.o\
			  MSG_DM_DC_DOMAIN_DBINFO_GET.pb.o CrossDomainInfoService.o MSG_DC_DM_PING.pb.o\
			  GenericInfoService.o CustomizedServiceAcceptor.o main.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(LDFLAGS)
