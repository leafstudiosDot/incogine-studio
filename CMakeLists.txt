cmake_minimum_required(VERSION 3.26.3)
project(IncogineStudio)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE CPP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE H_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

set(SOURCES ${CPP_SOURCES} ${H_SOURCES})

add_executable(incostudio WIN32 ${SOURCES})