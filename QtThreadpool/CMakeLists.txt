
cmake_minimum_required(VERSION 3.2.3)
#ATTENTION: If you use CMake with QtCreator, please use the latest version of CMake and Qt to avoid a auto-complete problem in QtCreator
project(QtThreadpool)

#Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
#Qt5
include_directories(${CMAKE_SOURCE_DIR}/Concurrent)
add_library(QtThreadpool qthreadpoolbridge.h qthreadpoolbridge.cpp)

target_link_libraries(QtThreadpool Qt5::Core Concurrent)
