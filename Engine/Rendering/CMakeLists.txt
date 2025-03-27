add_library(MLEngine_Rendering STATIC)
MLDetectSources(MLEngine_Rendering)
MLConfigureTarget(MLEngine_Rendering)
target_compile_definitions(MLEngine_Rendering PUBLIC ML_RENDERING)

target_link_libraries(MLEngine_Rendering PRIVATE
                      MLEngine_CoreInterfaces
                      MLEngine_Platform
                      MLEngine_HeaderOnlyLibs
                      SDL3::SDL3
                      glad
                      glm
)