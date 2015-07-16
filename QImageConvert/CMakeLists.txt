
cmake_minimum_required(VERSION 3.2.0)
#ATTENTION: If you use CMake with QtCreator, please use the latest version of CMake and Qt to avoid a auto-complete problem in QtCreator
project(QImageConvert)

#Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Gui REQUIRED)
#Qt5
include_directories(${CMAKE_SOURCE_DIR}/libImage)
include_directories(${CMAKE_SOURCE_DIR}/libMessager)
add_library(QImageConvert qimageconvert.h qimageconvert.cpp)

target_link_libraries(QImageConvert Qt5::Gui libImage libMessager)
