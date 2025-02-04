//
// Created by Lama on 02/02/2025.
//
#include "Rendering/Context.h"

#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_log.h>

#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>


namespace MLEngine
{
    void debugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                         const GLchar* message, const void* userParam)
    {
        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        SDL_Log("---------------");
        SDL_Log("Debug message (%u): %s", id, message);

        switch (source)
        {
            case GL_DEBUG_SOURCE_API: SDL_Log("Source: API");
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: SDL_Log("Source: Window System");
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: SDL_Log("Source: Shader Compiler");
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY: SDL_Log("Source: Third Party");
                break;
            case GL_DEBUG_SOURCE_APPLICATION: SDL_Log("Source: Application");
                break;
            case GL_DEBUG_SOURCE_OTHER: SDL_Log("Source: Other");
                break;
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR: SDL_Log("Type: Error");
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: SDL_Log("Type: Deprecated Behaviour");
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: SDL_Log("Type: Undefined Behaviour");
                break;
            case GL_DEBUG_TYPE_PORTABILITY: SDL_Log("Type: Portability");
                break;
            case GL_DEBUG_TYPE_PERFORMANCE: SDL_Log("Type: Performance");
                break;
            case GL_DEBUG_TYPE_MARKER: SDL_Log("Type: Marker");
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP: SDL_Log("Type: Push Group");
                break;
            case GL_DEBUG_TYPE_POP_GROUP: SDL_Log("Type: Pop Group");
                break;
            case GL_DEBUG_TYPE_OTHER: SDL_Log("Type: Other");
                break;
        }

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH: SDL_Log("Severity: high");
                break;
            case GL_DEBUG_SEVERITY_MEDIUM: SDL_Log("Severity: medium");
                break;
            case GL_DEBUG_SEVERITY_LOW: SDL_Log("Severity: low");
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: SDL_Log("Severity: notification");
                break;
        }
    }

    GraphicsContext::GraphicsContext(const Window* window)
    {
        SDL_assert(window->GetWindowHandle() != nullptr);
        window_handle = static_cast<SDL_Window*>(window->GetWindowHandle());

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

        SDL_Log("[GPU] OPENGL Context initialized");
        SDL_Log("[GPU] Renderer: %s", glGetString(GL_RENDERER));
        SDL_Log("[GPU] Vendor : %s", glGetString(GL_VENDOR));
        SDL_Log("[GPU] Version : %s", glGetString(GL_VERSION));
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
