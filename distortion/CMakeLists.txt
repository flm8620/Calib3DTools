cmake_minimum_required(VERSION 3.2.3)
project(DistortionCorrection)

include_directories(${CMAKE_SOURCE_DIR}/libMessager)
include_directories(${CMAKE_SOURCE_DIR}/libImage)
include_directories(${CMAKE_SOURCE_DIR}/libNumerics)

include_directories(libDistortion)
include_directories(libLineDetection)
include_directories(libMisc)

add_subdirectory(libDistortion)
add_subdirectory(libLineDetection)
add_subdirectory(libMisc)

add_library(DistortionPoly distCorrection.cpp distCorrection.h)

target_link_libraries(DistortionPoly linedetect distortion misc)
target_link_libraries(DistortionPoly libImage libNumerics libMessager)
