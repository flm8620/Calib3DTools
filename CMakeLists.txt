cmake_minimum_required(VERSION 2.8.11)

project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)

file(GLOB SOURCE_FILES "*.cpp" "*.h")

include_directories(ClickImage)
add_subdirectory(ClickImage)
# Tell CMake to create the executable
add_executable(mainInterface ${SOURCE_FILES})

# Use the Widgets module from Qt 5.
target_link_libraries(mainInterface ClickImage Qt5::Widgets Qt5::Concurrent)
