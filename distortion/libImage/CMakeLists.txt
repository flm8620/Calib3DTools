cmake_minimum_required(VERSION 2.6)
add_library(image correction.h image.cpp image.h pgm_io.cpp pgm_io.h spline.cpp spline.h)
target_link_libraries(image misc)
