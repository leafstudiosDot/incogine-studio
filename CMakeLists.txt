cmake_minimum_required(VERSION 3.26.3)
project(IncogineStudio)

set(TARGET_NAME incostudio)
set(APP_NAME "Incogine Studio")

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE CPP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE H_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE MM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.mm)

set(SOURCES ${CPP_SOURCES} ${H_SOURCES})

if(WIN32)
    add_executable(${TARGET_NAME} WIN32 ${SOURCES})
elseif(APPLE)
    add_executable(${TARGET_NAME} MACOSX_BUNDLE ${MM_SOURCES} ${H_SOURCES})

    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    target_link_libraries(${TARGET_NAME} ${COCOA_LIBRARY})

    set_source_files_properties(${MM_SOURCES} PROPERTIES COMPILE_FLAGS "-fobjc-arc")

    set_target_properties(${TARGET_NAME} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/misc/Info.plist"
        MACOSX_BUNDLE_BUNDLE_NAME "${APP_NAME}"
    )
else()
    add_executable(${TARGET_NAME} ${SOURCES})
endif()