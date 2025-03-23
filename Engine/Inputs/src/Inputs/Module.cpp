//
// Created by lama on 20/03/25.
//
#include "Inputs/Module.h"

#include "Platform/PlatformEvent.h"

namespace MLEngine
{
    void InputModule::SetCaptureMouse(bool capture)
    {
        SDL_SetWindowRelativeMouseMode(window, capture);
    }

    void InputModule::ProcessEvent(const PlatformEvent* event)
    {
        ModuleInterface::ProcessEvent(event);

        SDL_Event* sdl_event = static_cast<SDL_Event*>(event->Event);
        for (const auto& callback : subscribers[sdl_event->type]) { callback(event); }
        switch (sdl_event->type)
        {
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            keyboardState[sdl_event->key.scancode] = sdl_event->type == SDL_EVENT_KEY_DOWN;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            mouseButtonState[sdl_event->button.button] = sdl_event->type == SDL_EVENT_MOUSE_BUTTON_DOWN;
            break;
        case SDL_EVENT_MOUSE_MOTION:
            mousePosition = {sdl_event->motion.x, sdl_event->motion.y};
            relMouseMotion = {sdl_event->motion.xrel, sdl_event->motion.yrel};
            break;
        default:
            break;
        }
    }
}
