cmake_minimum_required(VERSION 3.30)
project(MLEngine C CXX)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POLICY_DEFAULT_CMP0169 OLD) #allow FetchContent_Populate to be called directly

add_subdirectory(Libs)
add_subdirectory(Engine)
target_link_libraries(MLEngine_Engine PRIVATE MLEngine_Libs)

if (PROJECT_IS_TOP_LEVEL)
    add_custom_target(copy_assets ALL
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets
            COMMENT "Copying Assets folder to binary directory on failure"
    )
    add_executable(MLEngine_main main.cpp)
    target_link_libraries(MLEngine_main PRIVATE MLEngine_Engine MLEngine_Libs)
    add_dependencies(MLEngine_main copy_assets)
endif ()