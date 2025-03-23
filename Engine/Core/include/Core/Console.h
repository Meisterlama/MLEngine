//
// Created by Lama on 04/02/2025.
//
#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace MLEngine
{
    class Console
    {
    public:
        Console();

        ~Console() = default;

        bool ExecuteCommand(const std::string& command);

        void RegisterCommand(const std::string& name, const std::string& description,
                             std::function<void()> commandFunc);

        void RenderConsole();

        void Log(const std::string& message);

        void ToggleConsole(bool isOpened);

        void ToggleConsole();

    private:
        bool isConsoleOpened = true;

        std::vector<std::string> outputHistory{};
        std::string inputField{};
        std::unordered_map<std::string, std::function<void()>> commands{};
        std::unordered_map<std::string, std::string> commandsDescription{};
    };
}
