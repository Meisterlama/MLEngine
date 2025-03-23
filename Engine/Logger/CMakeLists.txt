add_library(MLEngine_Logger)
MLDetectSources(MLEngine_Logger)
target_link_libraries(MLEngine_Logger PRIVATE
        MLEngine_CoreInterfaces
        fmt::fmt
)