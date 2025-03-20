add_library(MLEngine_Engine INTERFACE)
set_target_properties(MLEngine_Engine PROPERTIES ${MLEngine_TargetProperties})
target_compile_options(MLEngine_Engine INTERFACE ${MLEngine_TargetCompileOptions})


add_subdirectory(Core)
target_link_libraries(MLEngine_Engine INTERFACE MLEngine_Core)

if (MLEngine_Options_Rendering)
    add_subdirectory(Rendering)
    target_link_libraries(MLEngine_Engine INTERFACE MLEngine_Rendering)
endif ()



