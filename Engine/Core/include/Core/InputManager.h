//
// Created by Lama on 04/02/2025.
//
#pragma once
#include <functional>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <SDL3/SDL.h>

namespace MLEngine {
    class InputManager {
    public:
        using EventCallback = std::function<void(const SDL_Event &)>;

        static InputManager &GetInstance() {
            static InputManager instance;
            return instance;
        }

        void OnEvent(const SDL_Event &event) {
            for (const auto &callback: subscribers[event.type]) { callback(event); }
            switch (event.type) {
                case SDL_EVENT_KEY_DOWN:
                case SDL_EVENT_KEY_UP:
                    keyboardState[event.key.scancode] = event.type == SDL_EVENT_KEY_DOWN;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    mouseButtonState[event.button.button] = event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
                    break;
                case SDL_EVENT_MOUSE_MOTION:
                    mousePosition = {event.motion.x, event.motion.y};
                    relMouseMotion = {event.motion.xrel, event.motion.yrel};
                    break;
            }
        }

        bool IsKeyPressed(SDL_Scancode key) { return keyboardState[key]; }

        bool IsMouseButtonPressed(uint8_t button) { return mouseButtonState[button]; }

        glm::vec2 GetMousePosition() const { return mousePosition; }

        glm::vec2 GetMouseRelMotion() const { return relMouseMotion; }

        void SubscribeToEvent(SDL_EventType type, const EventCallback &callback) {
            subscribers[type].push_back(callback);
        }

        void UnsubscribeFromEvent(SDL_EventType type, const EventCallback &callback) {
            std::erase_if(
                subscribers[type],
                [&callback](const EventCallback &existingCallback) {
                    return callback.target_type() == existingCallback.target_type();
                });
        }

        void UnsubscribeFromAllEvents(SDL_EventType type) { subscribers[type].clear(); }
        void UnsubscribeFromAllEvents() { subscribers.clear(); }

        void ResetRelativeMouseMotion() { relMouseMotion = {0, 0}; }

    private:
        std::unordered_map<SDL_Scancode, bool> keyboardState{};

        std::unordered_map<uint8_t, bool> mouseButtonState{};
        glm::vec2 mousePosition{0, 0};
        glm::vec2 relMouseMotion{0, 0};

        std::unordered_map<uint32_t, std::vector<EventCallback> > subscribers{};

        InputManager() = default;

        ~InputManager() = default;

        InputManager(const InputManager &) = delete;

        InputManager &operator=(const InputManager &) = delete;
    };
}
