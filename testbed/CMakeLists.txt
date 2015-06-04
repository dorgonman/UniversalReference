cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (testbed CXX)


set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

SET (PROJ_SRCS src/Source.cpp)

set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -O2 -g -Wall")
ADD_EXECUTABLE (testbed ${PROJ_SRCS})

