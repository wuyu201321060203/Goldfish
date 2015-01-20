#!/bin/sh

PROJECT_DIR=$HOME/GoldFish
SRC_DIR=$PROJECT_DIR/proto
DST_DIR=.
INCLUDE_DIR=$PROJECT_DIR/include/protocol
DST_SRC_DIR=$PROJECT_DIR/src/protocol

if [ $1 = "all" ]; then
    protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/*.proto
    mv ./*.pb.h $INCLUDE_DIR
    mv ./*.pb.cc $DST_SRC_DIR
else
    protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/$1.proto
    mv ./$1.pb.h $INCLUDE_DIR
    mv ./$1.pb.cc $DST_SRC_DIR
fi