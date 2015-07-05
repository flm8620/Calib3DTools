
cmake_minimum_required(VERSION 3.2.3)
#ATTENTION: If you use CMake with QtCreator, please use the latest version of CMake and Qt to avoid a auto-complete problem in QtCreator
project(mainInterface)

#Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_BUILD_TYPE Debug)
find_package(Qt5Widgets)
find_package(Qt5Concurrent)
#Qt5

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(libNumerics)
add_subdirectory(Concurrent)
add_subdirectory(libImage)
add_subdirectory(libMessager)
add_subdirectory(QImageConvert)

add_subdirectory(ClickImage)
add_subdirectory(distortion)
add_subdirectory(KMatrixModule)

add_subdirectory(OpenMVG_simple)

include_directories(QImageConvert)
include_directories(libMessager)
include_directories(libImage)
include_directories(distortion)
include_directories(KMatrixModule)
include_directories(ClickImage)
include_directories(OpenMVG_simple)



file(GLOB SOURCE_FILES "*.cpp" "*.h")
add_executable(mainInterface ${SOURCE_FILES})

target_link_libraries(mainInterface
Concurrent
#pthread
ClickImage
libMessager
libImage
QImageConvert

DistortionPoly
KMatrixModule
strecha

Qt5::Widgets
Qt5::Concurrent
)
