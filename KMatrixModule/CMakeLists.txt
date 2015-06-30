cmake_minimum_required(VERSION 3.2.3)
#ATTENTION: If you use CMake with QtCreator, please use the latest version of CMake and Qt to avoid a auto-complete problem in QtCreator
project(KMatrixFinal)

#Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Gui)
#Qt5

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_SOURCE_DIR}/libNumerics)
include_directories(${CMAKE_SOURCE_DIR}/QImageConvert)
include_directories(${CMAKE_SOURCE_DIR}/libImage)
include_directories(${CMAKE_SOURCE_DIR}/libMessager)

include_directories(Kmatrix)
add_subdirectory(Kmatrix)
include_directories(ellipseCenter)
add_subdirectory(ellipseCenter)

add_library(KMatrixModule kmatrixsolve.h kmatrixsolve.cpp)

target_link_libraries(KMatrixModule kmatrixLib circleDetect)
target_link_libraries(KMatrixModule Qt5::Gui QImageConvert libImage libNumerics libMessager)
