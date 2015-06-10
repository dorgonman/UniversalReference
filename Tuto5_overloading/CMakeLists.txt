cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (Tuto5_overloading CXX)

include(../cmake/CommonSetting.cmake)

SET (PROJ_SRCS cpp/Source.cpp)



ADD_EXECUTABLE (Tuto5_overloading ${PROJ_SRCS})

include(../cmake/CommonLink.cmake)
