#include "Core/EntryPoint.h"
#include "Core/Engine.h"

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    MLEngine::Engine *engine = new MLEngine::Engine();
    *appstate = engine;
    engine->Init(MLEngine::CreateApplication());
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    MLEngine::Engine *engine = static_cast<MLEngine::Engine *>(appstate);
    engine->ProcessEvent(event);
    if (engine->ShouldQuit()) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    MLEngine::Engine *engine = static_cast<MLEngine::Engine *>(appstate);
    engine->Update();
    if (engine->ShouldQuit()) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    MLEngine::Engine *engine = static_cast<MLEngine::Engine *>(appstate);
    engine->Shutdown();
}
