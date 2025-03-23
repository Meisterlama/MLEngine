message(STATUS "Configuring MLEngine Libraries")

add_library(MLEngine_HeaderOnlyLibs INTERFACE)
target_include_directories(MLEngine_HeaderOnlyLibs INTERFACE include)

add_subdirectory(glad)
include(Libs/imgui)
include(Libs/SDL3)
include(Libs/glm)
include(Libs/flecs)
include(Libs/fmt)

find_package(OpenGL REQUIRED)

message(STATUS "All MLEngine Libraries have been configured")
