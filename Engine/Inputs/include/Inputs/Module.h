//
// Created by Lama on 04/02/2025.
//
#pragma once
#include <functional>
#include <unordered_map>
#include <CoreInterfaces/ModuleLocator.h>
#include <glm/vec2.hpp>
#include <SDL3/SDL.h>

#include "CoreInterfaces/ModuleInterface.h"

namespace MLEngine
{
    class InputModule : public ModuleInterface
    {
    public:
        InputModule() : ModuleInterface("Input")
        {
        };
        ~InputModule() override = default;
        using EventCallback = std::function<void(const PlatformEvent*)>;

        bool IsKeyPressed(SDL_Scancode key) { return keyboardState[key]; }

        bool IsMouseButtonPressed(uint8_t button) { return mouseButtonState[button]; }

        glm::vec2 GetMousePosition() const { return mousePosition; }

        glm::vec2 GetMouseRelMotion() const { return relMouseMotion; }

        void SetCaptureMouse(bool capture);

        void SubscribeToEvent(SDL_EventType type, const EventCallback& callback)
        {
            subscribers[type].push_back(callback);
        }

        void UnsubscribeFromEvent(SDL_EventType type, const EventCallback& callback)
        {
            std::erase_if(
                subscribers[type],
                [&callback](const EventCallback& existingCallback)
                {
                    return callback.target_type() == existingCallback.target_type();
                });
        }

        void UnsubscribeFromAllEvents(SDL_EventType type) { subscribers[type].clear(); }
        void UnsubscribeFromAllEvents() { subscribers.clear(); }

        void ResetRelativeMouseMotion() { relMouseMotion = {0, 0}; }

    private:
        SDL_Window* window = nullptr;

        std::unordered_map<SDL_Scancode, bool> keyboardState{};

        std::unordered_map<Uint8, bool> mouseButtonState{};
        glm::vec2 mousePosition{0, 0};
        glm::vec2 relMouseMotion{0, 0};

        std::unordered_map<Uint32, std::vector<EventCallback>> subscribers{};

    public:
        void ProcessEvent(const PlatformEvent* event) override;
    };
}
