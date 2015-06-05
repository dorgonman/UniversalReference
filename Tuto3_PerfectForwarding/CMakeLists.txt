cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (Tuto3_PerfectForwarding CXX)

include(../cmake/CommonSetting.cmake)

SET (PROJ_SRCS cpp/Source.cpp)


ADD_EXECUTABLE (Tuto3_PerfectForwarding ${PROJ_SRCS})

include(../cmake/CommonLink.cmake)
