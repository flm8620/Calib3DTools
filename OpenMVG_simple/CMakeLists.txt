
# Copyright (c) 2012, 2013 openMVG authors.

# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(openMVG C CXX)

# ==============================================================================
# OpenMVG build options
# ==============================================================================
OPTION(OpenMVG_BUILD_TESTS "Build OpenMVG tests" OFF)
OPTION(OpenMVG_BUILD_EXAMPLES "Build OpenMVG example applications. Does not affect binaries under 'software'" ON)
option(OpenMVG_BUILD_COVERAGE "Enable code coverage generation (gcc only)" OFF)
OPTION(OpenMVG_USE_OPENMP "Enable OpenMP parallelization" ON)

# By default build in Release mode
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release")
ENDIF(NOT CMAKE_BUILD_TYPE)

IF (WIN32)
  ADD_DEFINITIONS(-DNOMINMAX)
ENDIF (WIN32)

# ==============================================================================
# Additional cmake find modules
# ==============================================================================
SET(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmakeFindModules)
INCLUDE(OptimizeForArchitecture)
OptimizeForArchitecture()
IF (SSE2_FOUND)
  IF (MSVC AND NOT ${CMAKE_CL_64})
    ADD_DEFINITIONS(/arch:SSE2)
  ENDIF (MSVC AND NOT ${CMAKE_CL_64})
  ADD_DEFINITIONS(-DUSE_SSE)
ENDIF (SSE2_FOUND)
IF (UNIX AND NOT OpenMVG_BUILD_COVERAGE)
  SET(CMAKE_C_FLAGS_RELEASE "-O3")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
ENDIF ()






# Configure Eigen to use only MPL2 licensed code
ADD_DEFINITIONS(-DEIGEN_MPL2_ONLY)

SET(OpenMVG_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/eigen
)

INCLUDE_DIRECTORIES(${OpenMVG_INCLUDES})

ADD_SUBDIRECTORY(openMVG)

SET(OpenMVG_LIBS openMVG_multiview)
# concat lists
SET(OpenMVG_LIBS "${OpenMVG_LIBS}" ${openMVG_linearProgramming})
SET(OpenMVG_LIBS "${OpenMVG_LIBS}"
  ${OPENMVG_LIBRARY_DEPENDENCIES} CACHE STRING "openMVG library names")
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libMessager)
add_library(strecha strecha.cpp strecha.h)
TARGET_LINK_LIBRARIES(strecha openMVG_multiview libMessager)



