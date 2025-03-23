//
// Created by Lama on 02/02/2025.
//
#include "Rendering/Context.h"

#include <SDL3/SDL_assert.h>

#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>

#include "Logger/Module.h"


namespace MLEngine
{
    void debugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                         const GLchar* message, const void* userParam)
    {
        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        MLLogTrace("---------------");
        MLLogTrace("Debug message ({}): {}", id, message);

        switch (source)
        {
            case GL_DEBUG_SOURCE_API: MLLogTrace("Source: API");
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: MLLogTrace("Source: Window System");
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: MLLogTrace("Source: Shader Compiler");
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY: MLLogTrace("Source: Third Party");
                break;
            case GL_DEBUG_SOURCE_APPLICATION: MLLogTrace("Source: Application");
                break;
            case GL_DEBUG_SOURCE_OTHER: MLLogTrace("Source: Other");
                break;
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR: MLLogTrace("Type: Error");
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: MLLogTrace("Type: Deprecated Behaviour");
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: MLLogTrace("Type: Undefined Behaviour");
                break;
            case GL_DEBUG_TYPE_PORTABILITY: MLLogTrace("Type: Portability");
                break;
            case GL_DEBUG_TYPE_PERFORMANCE: MLLogTrace("Type: Performance");
                break;
            case GL_DEBUG_TYPE_MARKER: MLLogTrace("Type: Marker");
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP: MLLogTrace("Type: Push Group");
                break;
            case GL_DEBUG_TYPE_POP_GROUP: MLLogTrace("Type: Pop Group");
                break;
            case GL_DEBUG_TYPE_OTHER: MLLogTrace("Type: Other");
                break;
        }

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH: MLLogTrace("Severity: high");
                break;
            case GL_DEBUG_SEVERITY_MEDIUM: MLLogTrace("Severity: medium");
                break;
            case GL_DEBUG_SEVERITY_LOW: MLLogTrace("Severity: low");
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: MLLogTrace("Severity: notification");
                break;
        }
    }

    GraphicsContext::GraphicsContext(void* window)
    {
        window_handle = (SDL_Window*)window;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        gl_context = SDL_GL_CreateContext(window_handle);
        SDL_assert(gl_context != nullptr);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));

        MLLogTrace("[GPU] OPENGL Context initialized");
        MLLogTrace("[GPU] Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        MLLogTrace("[GPU] Vendor : {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        MLLogTrace("[GPU] Version : {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
        if (GLAD_GL_KHR_debug)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback((GLDEBUGPROC) debugGLCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
            glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 0, nullptr, GL_FALSE);
        }

        SDL_GL_MakeCurrent(window_handle, gl_context);
        SDL_GL_SetSwapInterval(1);

        renderer = new Renderer();
    }

    GraphicsContext::~GraphicsContext()
    {
        if (renderer != nullptr) { delete renderer; }
        if (gl_context) { SDL_GL_DestroyContext(gl_context); }
    }

    void GraphicsContext::SwapBuffers() { SDL_GL_SwapWindow(window_handle); }
}
