add_library(MLEngine_Core)
MLDetectSources(MLEngine_Core)
target_link_libraries(MLEngine_Core PUBLIC
                      MLEngine_CoreInterfaces
                      MLEngine_HeaderOnlyLibs
                      MLEngine_Rendering
                      MLEngine_Inputs
                      MLEngine_Logger
                      MLEngine_Resource
                      MLEngine_Platform
                      imgui
                      flecs::flecs_static
                      glm::glm
)
