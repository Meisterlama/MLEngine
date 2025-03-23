//
// Created by lama on 20/03/25.
//
#include "Inputs/InputModule.h"

namespace MLEngine
{
    void InputModule::SetCaptureMouse(bool capture)
    {
        SDL_SetWindowRelativeMouseMode(window, capture);
    }

    void InputModule::Init()
    {
    }

    void InputModule::Update()
    {
    }

    void InputModule::ProcessEvent(SDL_Event* event)
    {
        for (const auto& callback : subscribers[event->type]) { callback(event); }
        switch (event->type)
        {
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            keyboardState[event->key.scancode] = event->type == SDL_EVENT_KEY_DOWN;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            mouseButtonState[event->button.button] = event->type == SDL_EVENT_MOUSE_BUTTON_DOWN;
            break;
        case SDL_EVENT_MOUSE_MOTION:
            mousePosition = {event->motion.x, event->motion.y};
            relMouseMotion = {event->motion.xrel, event->motion.yrel};
            break;
        }
    }

    void InputModule::Shutdown()
    {
    }
}
