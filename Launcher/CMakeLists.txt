add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets
        COMMENT "Copying Assets folder to binary directory on failure"
)

file(GLOB_RECURSE LAUNCHER_SRC CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_executable(MLEngine_Launcher ${LAUNCHER_SRC})
target_include_directories(MLEngine_Launcher PRIVATE include)

set_target_properties(MLEngine_Launcher PROPERTIES ${MLEngine_TargetProperties})
target_compile_options(MLEngine_Launcher PRIVATE ${MLEngine_TargetCompileOptions})

target_link_libraries(MLEngine_Launcher PUBLIC MLEngine_Engine)
add_dependencies(MLEngine_Launcher copy_assets)