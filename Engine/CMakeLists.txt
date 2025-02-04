file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS src/*.cpp include/*.h)


add_library(MLEngine_Engine STATIC
       ${ENGINE_SRC}
)
target_include_directories(MLEngine_Engine PUBLIC include)

if (MSVC)
    target_compile_options(MLEngine_Engine PRIVATE /W4)
else ()
    target_compile_options(MLEngine_Engine PRIVATE -Wall -Wextra -Wpedantic)
endif ()