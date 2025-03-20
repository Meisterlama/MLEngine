file(GLOB_RECURSE RENDERING_SRC CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_library(MLEngine_Rendering SHARED ${RENDERING_SRC})
target_include_directories(MLEngine_Rendering PUBLIC include)

set_target_properties(MLEngine_Rendering PROPERTIES ${MLEngine_TargetProperties})
target_compile_options(MLEngine_Rendering PRIVATE ${MLEngine_TargetCompileOptions})
target_compile_definitions(MLEngine_Rendering PUBLIC ML_RENDERING)

target_link_libraries(MLEngine_Rendering PUBLIC
        MLEngine_HeaderOnlyLibs
        SDL3::SDL3
        glad
        glm
        imgui
)