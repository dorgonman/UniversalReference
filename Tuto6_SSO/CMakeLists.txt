cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (Tuto6_SSO CXX)

include(../cmake/CommonSetting.cmake)

SET (PROJ_SRCS cpp/Source.cpp)



ADD_EXECUTABLE (Tuto6_SSO ${PROJ_SRCS})

include(../cmake/CommonLink.cmake)
