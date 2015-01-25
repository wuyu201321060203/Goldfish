MUDUO_DIRECTORY = $(HOME)/build/debug-install
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
OOZDB_INCLUDE = ../OOzdb
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
		  -lmysqlclient -llua5.1 -ldl -lboost_program_options -lprotobuf

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -ggdb3 -Wall -Wextra -pthread -I$(MUDUO_INCLUDE) -I$(OOZDB_INCLUDE)\
			-I$(DM_INCLUDE) -std=c++11 -DTEST

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = dm_unittest

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

initializer_unittest.o : $(USER_DIR)/initializer_unittest.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

loader_unittest.o : $(USER_DIR)/loader_unittest.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

dbacceptor_unittest.o : $(USER_DIR)/dbacceptor_unittest.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

token_unittest.o : $(USER_DIR)/token_unittest.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

crossinfoservice_unittest.o : $(USER_DIR)/crossinfoservice_unittest.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

util_unittest.o : $(USER_DIR)/util_unittest.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ConfigLoader.o : $(DM_SRC_DIR)/ConfigLoader.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Options.o : $(DM_SRC_DIR)/Options.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Initializer.o : $(DM_SRC_DIR)/Initializer.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ProtobufCodec.o : $(DM_SRC_DIR)/ProtobufCodec.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_CONFIG_PERSISTENCE.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_CONFIG_PERSISTENCE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_CONFIG_LOOKUP.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_CONFIG_LOOKUP.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DC_DM_CONFIG_DELETE.pb.o : $(PROTO_SRC_DIR)/MSG_DC_DM_CONFIG_DELETE.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DM_DC_DOMAIN_DBINFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_DM_DC_DOMAIN_DBINFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.o : $(PROTO_SRC_DIR)/MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

DbAcceptor.o : $(DM_SRC_DIR)/DbAcceptor.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Token.o : $(DM_SRC_DIR)/Token.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

util.o : $(DM_SRC_DIR)/util.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

CrossDomainInfoService.o : $(DM_SRC_DIR)/CrossDomainInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

DbInfoService.o : $(DM_SRC_DIR)/DbInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

SysInfoService.o : $(DM_SRC_DIR)/SysInfoService.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

dm_unittest : gtest_main.a initializer_unittest.o loader_unittest.o dbacceptor_unittest.o ConfigLoader.o Options.o\
			  Initializer.o ProtobufCodec.o Connection.o ConnectionPool.o MemoryOperation.o MysqlConnection.o \
			  MysqlPreparedStatement.o MysqlResultSet.o PreparedStatement.o ResultSet.o \
			  StringBuffer.o StrOperation.o TimeOperation.o URL.o MSG_DC_DM_CONFIG_PERSISTENCE.pb.o\
			  DbAcceptor.o MSG_DC_DM_CONFIG_LOOKUP.pb.o MSG_DC_DM_CONFIG_DELETE.pb.o\
			  token_unittest.o Token.o util_unittest.o util.o CrossDomainInfoService.o DbInfoService.o\
		      MSG_DM_DC_DOMAIN_DBINFO_GET.pb.o MSG_CLIENT_DM_CROSS_DBINFO_GET.pb.o\
			  SysInfoService.o MSG_DM_DC_DOMAIN_SYSINFO_GET.pb.o MSG_CLIENT_DM_CROSS_SYSINFO_GET.pb.o\
			  crossinfoservice_unittest.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(LDFLAGS)
