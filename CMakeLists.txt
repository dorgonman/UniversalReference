cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT (UniversalReference CXX)


set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
 
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
 
add_subdirectory(testbed)
add_subdirectory(Tuto1_Move_semantics_1)
add_subdirectory(Tuto1_Move_semantics_2)
add_subdirectory(Tuto2_Rule_Of_Five)
add_subdirectory(Tuto2_Rule_of_zero)
add_subdirectory(Tuto3_PerfectForwarding)
add_subdirectory(Tuto4_UR_and_Type_Trait)