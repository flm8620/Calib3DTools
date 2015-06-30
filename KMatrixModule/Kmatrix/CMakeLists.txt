CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(Kmatrix)
include_directories(${CMAKE_SOURCE_DIR}/libNumerics)
include_directories(${CMAKE_SOURCE_DIR}/libMessager)
SET(SRC ellipse_operations.h Hmatrix.h jac_eqs.h Kmatrix.h kmatrix_main.cpp kmatrix_main.h)

add_library(kmatrixLib ${SRC})
target_link_libraries(kmatrixLib libNumerics libMessager)
