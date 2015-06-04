cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (Tuto2_Rule_of_zero CXX)


set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp)

SET (PROJ_SRCS cpp/Source.cpp)

IF(UNIX)
	set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -O2 -g -Wall")
ENDIF()

ADD_EXECUTABLE (Tuto2_Rule_of_zero ${PROJ_SRCS})

