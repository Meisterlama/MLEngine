cmake_minimum_required(VERSION 3.30)
project(MLEngine C CXX)

# Add the cmake directory to the global module path so we can include project
# defined .cmake files anywhere in the project
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Make what's inside of these files globally available to the project
include(MLEngineGlobals)
include(MLEngineDeps)
include(MLEngineUtils)

# All projects options should go here
option(MLEngine_Options_SharedLibrary "Build the engine as a shared library" ON)
option(MLEngine_Options_Rendering "Build Rendering Module" ON)
option(MLEngine_Options_Launcher "Use project defined main.cpp" ON)

# Building MLEngine
add_subdirectory(Libs)
add_subdirectory(Engine)

# Using MLEngine
if (MLEngine_Options_Launcher)
    add_subdirectory(Launcher)
endif()