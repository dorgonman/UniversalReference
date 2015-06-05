cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (LibCommonUtil CXX)

include(../cmake/UtilMacro.cmake)

include(../cmake/CommonSetting.cmake)

file(GLOB PROJ_SRCS
 	"cpp/Public/*.h"
    "cpp/Public/*.cpp"
)

source_group_by_dir(PROJ_SRCS)


file(GLOB PLATFORM_SRCS
 	"cpp/Platform/standard/*.h"
    "cpp/Platform/standard/*.cpp"
)

source_group_by_dir(PLATFORM_SRCS)

add_executable(LibCommonUtil ${PLATFORM_SRCS} ${PROJ_SRCS})
add_library(LibCommonUtilShared SHARED ${PROJ_SRCS})
add_library(LibCommonUtilStatic STATIC ${PROJ_SRCS})

#generate_export_header(LibCommonUtil EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/LibCommonUtil/cpp/Public/Timer.h)