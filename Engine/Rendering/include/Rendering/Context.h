//
// Created by Lama on 02/02/2025.
//
#pragma once

#include "Renderer.h"
#include <SDL3/SDL_video.h>

namespace MLEngine {
    class GraphicsContext {
        public:
        GraphicsContext(void* window_handle);

        ~GraphicsContext();

        void SwapBuffers();

        void *GetContextHandle() { return gl_context; };
        Renderer *GetRenderer() { return renderer; };

    private:
        SDL_Window *window_handle = nullptr;
        SDL_GLContext gl_context;
        Renderer *renderer = nullptr;
    };
}
