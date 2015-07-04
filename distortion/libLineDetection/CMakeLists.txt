cmake_minimum_required(VERSION 3.2.3)

#include_directories(${CMAKE_SOURCE_DIR}/libMessager)
#include_directories(${CMAKE_SOURCE_DIR}/libImage)

file(GLOB SOURCE_FILES "*.cpp" "*.h")
add_library(linedetect ${SOURCE_FILES})
target_link_libraries(linedetect libMessager libImage misc)
