cmake_minimum_required(VERSION 3.2.3)
#ATTENTION: If you use CMake with QtCreator, please use the latest version of CMake and Qt to avoid a auto-complete problem in QtCreator
project(Concurrent)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libMessager)
find_package( Threads )
add_library(
Concurrent
readwritelock.cpp readwritelock.h
stlCallable.h
abstractthreadpool.cpp abstractthreadpool.h
simplethreadpool.cpp simplethreadpool.h
)
target_link_libraries(
Concurrent libMessager
${CMAKE_THREAD_LIBS_INIT}
)
