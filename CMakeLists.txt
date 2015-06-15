
cmake_minimum_required(VERSION 3.2.3)
#ATTENTION: If you use CMake with QtCreator, please use the latest version of CMake and Qt to avoid a auto-complete problem in QtCreator
project(mainInterface)

#Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
find_package(Qt5Concurrent)
#Qt5

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES "*.cpp" "*.h")

include_directories(ClickImage)
add_subdirectory(ClickImage)
include_directories(distortion)
add_subdirectory(distortion)

add_executable(mainInterface ${SOURCE_FILES})

target_link_libraries(mainInterface Qt5::Widgets Qt5::Concurrent ClickImage Distortion_poly)
