function(MLConfigureTarget _Target)
    set_target_properties(${_Target} PROPERTIES ${MLEngine_TargetProperties})
    target_compile_options(${_Target} PRIVATE ${MLEngine_TargetCompileOptions})
endfunction()

function(MLAddModule _Directory)
    add_subdirectory(${_Directory})
    target_link_libraries(${MLEngine_BuiltTarget} INTERFACE "MLEngine_${_Directory}")
endfunction()

function(MLCreateAndSelectEngineTarget)
    if (${MLEngine_Options_SharedLibrary})
        message(STATUS "Compiling MLEngine as a SHARED library")
        add_library(MLEngine_Engine_Shared SHARED)
        file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)
        target_sources(MLEngine_Engine_Shared PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp)
        add_library(MLEngine_Engine ALIAS MLEngine_Engine_Shared)
        set(MLEngine_BuiltTarget MLEngine_Engine_Shared PARENT_SCOPE)
    else ()
        message(STATUS "Compiling MLEngine as a STATIC library")
        add_library(MLEngine_Engine_Static INTERFACE)
        add_library(MLEngine_Engine ALIAS MLEngine_Engine_Static)
        set(MLEngine_BuiltTarget MLEngine_Engine_Static PARENT_SCOPE)
    endif ()
endfunction()

function(MLDetectSources _Target)
    string(REPLACE "MLEngine_" "" _Module ${_Target})

    file(GLOB_RECURSE MODULE_SRC CONFIGURE_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    )
    target_include_directories("${_Target}"
            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    )
    target_sources("${_Target}" PRIVATE ${MODULE_SRC})

    MLConfigureTarget("${_Target}")
endfunction()