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
    )
    target_include_directories(imgui PUBLIC
            "${imgui_SOURCE_DIR}"
            "${imgui_SOURCE_DIR}/backends"
    )
    target_link_libraries(imgui PRIVATE SDL3::SDL3)
endif ()