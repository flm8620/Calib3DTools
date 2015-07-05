cmake_minimum_required(VERSION 3.2.3)
project(DistortionCorrection)

INCLUDE_DIRECTORIES(
${CMAKE_SOURCE_DIR}/libMessager
${CMAKE_SOURCE_DIR}/libImage
${CMAKE_SOURCE_DIR}/libNumerics
${CMAKE_SOURCE_DIR}/Concurrent
libDistortion
libLineDetection
libMisc
)
add_subdirectory(libDistortion)
add_subdirectory(libLineDetection)
add_subdirectory(libMisc)

add_library(DistortionPoly distCorrection.cpp distCorrection.h)
target_include_directories(DistortionPoly PUBLIC
${CMAKE_SOURCE_DIR}/libMessager
${CMAKE_SOURCE_DIR}/libImage
${CMAKE_SOURCE_DIR}/libNumerics
${CMAKE_SOURCE_DIR}/Concurrent
libDistortion
libLineDetection
libMisc
)
target_link_libraries(DistortionPoly linedetect distortion misc
libImage libNumerics libMessager Concurrent)
