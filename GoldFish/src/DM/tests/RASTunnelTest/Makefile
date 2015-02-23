MUDUO_DIRECTORY = $(HOME)/build/debug-install
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
OOZDB_INCLUDE = ../../OOzdb
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
			-I$(DM_INCLUDE) -std=c++11 -DTEST

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

TESTS = RASServer

all : $(TESTS)

clean :
	rm -f $(TESTS)
	rm *.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

FwmRcProtocol.pb.o: $(PROTO_SRC_DIR)/FwmRcProtocol.pb.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

main.o: ./main.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ProtobufRASCodec.o: $(DM_SRC_DIR)/ProtobufRASCodec.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Initializer.o: $(DM_SRC_DIR)/Initializer.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ConfigLoader.o: $(DM_SRC_DIR)/ConfigLoader.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Options.o: $(DM_SRC_DIR)/Options.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ProtobufCodec.o: $(DM_SRC_DIR)/ProtobufCodec.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

RASServer : FwmRcProtocol.pb.o main.o ProtobufRASCodec.o ProtobufCodec.o Initializer.o\
			ConfigLoader.o Options.o Connection.o ConnectionPool.o MemoryOperation.o\
			MysqlConnection.o MysqlPreparedStatement.o MysqlResultSet.o\
			PreparedStatement.o ResultSet.o StringBuffer.o StrOperation.o\
			TimeOperation.o URL.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(LDFLAGS)
