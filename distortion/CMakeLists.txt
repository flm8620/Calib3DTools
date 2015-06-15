cmake_minimum_required(VERSION 2.6)
project(Distortion_Correction)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libDistortion)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libLineDetection)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libImage)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libNumerics)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libMisc)

add_subdirectory(libDistortion)
add_subdirectory(libImage)
add_subdirectory(libLineDetection)
add_subdirectory(libNumerics)
add_subdirectory(libMisc)

add_library(Distortion_poly polyEstimation.cpp distCorrection.cpp polyEstimation.h)
target_link_libraries(Distortion_poly image numerics linedetect distortion misc)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
