cmake_minimum_required(VERSION 2.6)

add_library(distortion  distortion.h)
target_link_libraries(distortion libNumerics)
