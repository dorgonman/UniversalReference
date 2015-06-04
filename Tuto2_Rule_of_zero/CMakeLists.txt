cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (Tuto2_Rule_of_zero CXX)

include(../cmake/CommonSetting.cmake)

SET (PROJ_SRCS cpp/Source.cpp)


ADD_EXECUTABLE (Tuto2_Rule_of_zero ${PROJ_SRCS})

