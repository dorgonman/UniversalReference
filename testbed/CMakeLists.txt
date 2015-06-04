cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (testbed CXX)

include(../cmake/UtilMacro.cmake)

include(../cmake/CommonSetting.cmake)



file(GLOB PROJ_SRCS
    "cpp/*.h"
    "cpp/*.cpp"
    "cpp/test/*.cpp"
    "cpp/test2/*.cpp"
)



source_group_by_dir(PROJ_SRCS)

ADD_EXECUTABLE (testbed ${PROJ_SRCS})

