file(GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_library(MLEngine_Core STATIC ${CORE_SRC})
target_include_directories(MLEngine_Core PUBLIC include)

set_target_properties(MLEngine_Core PROPERTIES ${MLEngine_TargetProperties})
target_compile_options(MLEngine_Core PRIVATE ${MLEngine_TargetCompileOptions})

target_link_libraries(MLEngine_Core PRIVATE
        MLEngine_HeaderOnlyLibs
        MLEngine_Rendering
        imgui
        SDL3::SDL3
        flecs::flecs_static
        glm::glm
)
