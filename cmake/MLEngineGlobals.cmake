set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

set(CMAKE_POLICY_DEFAULT_CMP0169 OLD) #allow FetchContent_Populate to be called directly

set(MLEngine_TargetProperties CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)

if (MSVC)
    set(MLEngine_TargetCompileOptions /W4)
elseif (GNU OR CLANG)
    set(MLEngine_TargetCompileOptions -Wall -Wextra -Wpedantic -fPIC)
endif ()

# TODO: Prevent definitions bleeding to 3rd party libs
if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(ML_MSVC)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(ML_GCC)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(ML_CLANG)
else()
    message(WARNING "Unknown compiler ! (${CMAKE_C_COMPILER_ID})")
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(MLPlatform Windows)
    add_compile_definitions(ML_WINDOWS)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(MLPlatform Linux)
    add_compile_definitions(ML_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(MLPlatform Apple)
    add_compile_definitions(ML_APPLE)
    message(FATAL_ERROR "Unsupported platform ! (${CMAKE_SYSTEM_NAME})")
elseif (CMAKE_SYSTEM_NAME STREQUAL "")
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(ML_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_definitions(ML_RELEASE)
endif ()
