add_library(MLEngine_Resource)
MLDetectSources(MLEngine_Resource)

target_link_libraries(MLEngine_Resource PRIVATE
                      MLEngine_CoreInterfaces
                      MLEngine_Logger
)