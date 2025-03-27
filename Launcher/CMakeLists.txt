# Automatically copy Assets folder to the build output directory
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets
        COMMENT "Copying Assets folder to binary directory"
)

add_executable(MLEngine_Launcher)
MLDetectSources(MLEngine_Launcher)
MLConfigureTarget(MLEngine_Launcher)

target_link_libraries(MLEngine_Launcher PUBLIC MLEngine_Engine)
add_dependencies(MLEngine_Launcher copy_assets)