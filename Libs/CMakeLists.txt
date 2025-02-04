add_library(MLEngine_Libs INTERFACE)

set(LIBS)

add_subdirectory(glad)
list(APPEND LIBS glad)

# Download CPM.cmake for dependency management
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
        ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

# Add dependencies here
CPMAddPackage(
        NAME imgui
        GITHUB_REPOSITORY ocornut/imgui
        GIT_TAG v1.91.8
        DOWNLOAD_ONLY True
)
if (imgui_ADDED)
    add_library(imgui STATIC)
    target_sources(imgui PRIVATE
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
    )
    target_include_directories(imgui PUBLIC
            "${imgui_SOURCE_DIR}"
            "${imgui_SOURCE_DIR}/backends"
            "${imgui_SOURCE_DIR}/misc/cpp"
    )
    target_link_libraries(imgui PRIVATE SDL3::SDL3)
    list(APPEND LIBS imgui)
endif ()

CPMAddPackage(
        NAME SDL
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG release-3.2.0
        OPTIONS
        "SDL_SHARED ON"
        "SDL_STATIC OFF"
        "SDL_TEST_LIBRARY OFF"
)
list(APPEND LIBS SDL3::SDL3)


CPMAddPackage("gh:SanderMertens/flecs#v4.0.4")
list(APPEND LIBS flecs::flecs_static)

CPMAddPackage("gh:g-truc/glm#1.0.1")
list(APPEND LIBS glm::glm)

find_package(OpenGL)
list(APPEND LIBS ${OPENGL_LIBRARIES} OpenGL32)

target_link_libraries(MLEngine_Libs INTERFACE ${LIBS})
target_include_directories(MLEngine_Libs INTERFACE include)