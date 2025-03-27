add_library(MLEngine_CoreInterfaces STATIC)
MLDetectSources(MLEngine_CoreInterfaces)

target_link_libraries(MLEngine_CoreInterfaces PUBLIC
                      MLEngine_Debug)