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

if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(ML_MSVC)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(ML_GCC)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(ML_CLANG)
else()
    message(WARNING "Unknown compiler ! (${CMAKE_C_COMPILER_ID})")
endif()

