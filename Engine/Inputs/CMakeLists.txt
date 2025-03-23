add_library(MLEngine_Inputs)
MLDetectSources(MLEngine_Inputs)
target_link_libraries(MLEngine_Inputs PRIVATE
        MLEngine_CoreInterfaces
        SDL3::SDL3
        glm
)
