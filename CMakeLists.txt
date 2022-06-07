cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Arithmetics)
project(${PROJECT_NAME})

# TODO(Kornyakov): not sure if these lines are needed
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(Arithmetics Arithmetics)
set(StackLib StackLib)
set(main main)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Arithmetics ${CMAKE_CURRENT_SOURCE_DIR}/StackLib) 

# BUILD
add_subdirectory(Arithmetics)
add_subdirectory(StackLib)
add_subdirectory(main)
add_subdirectory(gtest)
add_subdirectory(test)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")
