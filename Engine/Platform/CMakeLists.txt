add_library(MLEngine_Platform)
MLDetectSources(MLEngine_Platform)
target_link_libraries(MLEngine_Platform PRIVATE
                      MLEngine_CoreInterfaces
                      MLEngine_Logger
                      SDL3::SDL3
)