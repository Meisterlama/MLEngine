//
// Created by Lama on 02/02/2025.
//
#pragma once

#include <Window.h>

#include "Renderer.h"

namespace MLEngine
{
    class GraphicsContext
    {
    public:

        GraphicsContext(const Window* window);
        ~GraphicsContext();

        void SwapBuffers();

        void* GetContextHandle() { return gl_context; };
        Renderer* GetRenderer() { return renderer; };

    private:
        SDL_Window* window_handle = nullptr;
        SDL_GLContext gl_context;
        Renderer* renderer = nullptr;
    };
}
