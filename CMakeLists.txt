cmake_minimum_required(VERSION 3.30)
project(MLEngine C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(MLEngineGlobals)
include(MLEngineDeps)

option(MLEngine_Options_Rendering "Build Rendering Module" ON)
option(MLEngine_Options_Launcher "Use project defined main.cpp" ON)

add_subdirectory(Libs)
add_subdirectory(Engine)

if (MLEngine_Options_Launcher)
    add_subdirectory(Launcher)
endif()