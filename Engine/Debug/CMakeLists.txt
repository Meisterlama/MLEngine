add_library(MLEngine_Debug)
MLDetectSources(MLEngine_Debug)
target_compile_definitions(MLEngine_Debug PRIVATE ML_REDEFINE_HANDLE)
target_link_libraries(MLEngine_Debug PRIVATE
                      MLEngine_HeaderOnlyLibs
                      fmt::fmt
)