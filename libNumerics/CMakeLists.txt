CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(NumericsLibrary)

SET(SRC matrix.cpp matrix.h vector.cpp LMmin.h SVD.h ccmath_svd.cpp)

add_library(libNumerics ${SRC})
