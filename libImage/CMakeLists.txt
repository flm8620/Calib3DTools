cmake_minimum_required(VERSION 3.2.3)
#ATTENTION: If you use CMake with QtCreator, please use the latest version of CMake and Qt to avoid a auto-complete problem in QtCreator
project(ImageLibrary)

include_directories(${CMAKE_SOURCE_DIR}/libMessager)
include_directories(${CMAKE_SOURCE_DIR}/libNumerics)
file(GLOB SOURCE_FILES "*.cpp" "*.h")

add_library(libImage ${SOURCE_FILES})

target_link_libraries(libImage libMessager libNumerics)
