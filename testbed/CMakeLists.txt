cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (TEST_BED CXX)

SET (PROJ_SRCS Source.cpp)

set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -O0")
ADD_EXECUTABLE (testbed ${PROJ_SRCS})

