cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (Tuto4_UR_and_Type_Trait CXX)

include(../cmake/CommonSetting.cmake)

SET (PROJ_SRCS cpp/Source.cpp)



ADD_EXECUTABLE (Tuto4_UR_and_Type_Trait ${PROJ_SRCS})

