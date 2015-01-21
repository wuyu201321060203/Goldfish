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

CXX = g++
LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net_cpp11 -lmuduo_base_cpp11 -lpthread -lrt\
		  -lmysqlclient -llua5.1 -ldl -lboost_program_options -lprotobuf

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -ggdb3 -Wall -Wextra -pthread -DTEST -I$(MUDUO_INCLUDE) -I$(OOZDB_INCLUDE)\
			-I$(DM_INCLUDE) -std=c++11

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

ConfigLoader.o : $(DM_SRC_DIR)/ConfigLoader.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Options.o : $(DM_SRC_DIR)/Options.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Initializer.o : $(DM_SRC_DIR)/Initializer.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

ProtobufCodec.o : $(DM_SRC_DIR)/ProtobufCodec.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

dm_unittest : gtest_main.a initializer_unittest.o loader_unittest.o ConfigLoader.o Options.o\
			  Initializer.o ProtobufCodec.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(LDFLAGS)
