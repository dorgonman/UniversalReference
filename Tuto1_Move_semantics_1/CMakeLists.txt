cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (Tuto1_Move_semantics_1 CXX)


include(../cmake/CommonSetting.cmake)

SET (PROJ_SRCS cpp/Source.cpp)
IF(UNIX)
	set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -O2 -g -Wall")
ENDIF()

ADD_EXECUTABLE (Tuto1_Move_semantics_1 ${PROJ_SRCS})

