add_library(glad STATIC
        src/glad.c
)
target_include_directories(glad PUBLIC include)
target_compile_definitions(glad PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)
target_compile_options(glad PRIVATE -fPIC)