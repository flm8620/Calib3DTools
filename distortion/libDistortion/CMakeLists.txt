cmake_minimum_required(VERSION 2.6)

add_library(distortion distortion.cpp distortion.h)
target_link_libraries(distortion libNumerics)
