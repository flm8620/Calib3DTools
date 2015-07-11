cmake_minimum_required(VERSION 2.6)

project(Aberration_Correction)
include_directories(${CMAKE_SOURCE_DIR}/libImage)
include_directories(${CMAKE_SOURCE_DIR}/libNumerics)
include_directories(${CMAKE_SOURCE_DIR}/libMessager)

add_library(circleDetect abberation.h abberation.cpp centers.h main_centering.cpp main_centering.h)
target_link_libraries(circleDetect libNumerics libImage libMessager Qt5::Core)
