cmake_minimum_required(VERSION 3.2.0)
#ATTENTION: If you use CMake with QtCreator, please use the latest version of CMake and Qt to avoid a auto-complete problem in QtCreator
project(CamCompare)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_SOURCE_DIR}/libNumerics)
include_directories(${CMAKE_SOURCE_DIR}/libMessager)
include_directories(${CMAKE_SOURCE_DIR}/eigen)
add_library(CamCompare openMvgcompare.h camcompare.h camcompare.cpp)
target_link_libraries(CamCompare libNumerics libMessager)
