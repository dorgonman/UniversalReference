cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (Tuto1_Move_semantics_2 CXX)


include(../cmake/CommonSetting.cmake)

SET (PROJ_SRCS cpp/Source.cpp)


ADD_EXECUTABLE (Tuto1_Move_semantics_2 ${PROJ_SRCS})

include(../cmake/CommonLink.cmake)
