add_library(MLEngine_HeaderOnlyLibs INTERFACE)
target_include_directories(MLEngine_HeaderOnlyLibs INTERFACE include)

add_subdirectory(glad)

include(Libs/imgui)
include(Libs/SDL3)
include(Libs/glm)
include(Libs/flecs)

find_package(OpenGL REQUIRED)