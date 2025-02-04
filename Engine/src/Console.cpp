//
// Created by Lama on 04/02/2025.
//
#include "Console.h"

#include <ranges>
#include <utility>

#include "imgui.h"
#include "imgui_stdlib.h"

namespace MLEngine
{
    Console::Console()
    {
        RegisterCommand("clear", "Clears the console", [&]() { outputHistory.clear(); });
        RegisterCommand("help", "Display all commands with their description", [&]()
        {
            Log("Available commands:");
            for (const auto& command_name : commands | std::views::keys)
            {
                Log("- " + command_name + ": " + commands_description[command_name]);
            }
        });
    }

    bool Console::ExecuteCommand(const std::string& command)
    {
        if (const auto it = commands.find(command); it != commands.end())
        {
            it->second();  // Execute command function
            return true;
        }
        Log("ERROR: Unknown command " + command);
        return false;
    }

    void Console::RegisterCommand(const std::string& name, const std::string& description,
                                  std::function<void()> commandFunc)
    {
        commands[name] = std::move(commandFunc);
        commands_description[name] = description;
    }

    void Console::RenderConsole()
    {
        if (!isConsoleOpened) return;
        if (ImGui::Begin("Console", &isConsoleOpened))
        {
            if (ImGui::BeginChild("ConsoleOutput", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false,
                                  ImGuiWindowFlags_HorizontalScrollbar)
            )
            {
                for (const std::string& log : outputHistory)
                {
                    ImVec4 logColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  // Default: White

                    // Change log color based on message type
                    if (log.rfind("ERROR:", 0) == 0) logColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // Red for errors
                    else if (log.rfind("WARNING:", 0) == 0)
                        logColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);  // Yellow for warnings

                    ImGui::PushStyleColor(ImGuiCol_Text, logColor);
                    ImGui::TextUnformatted(log.c_str());
                    ImGui::PopStyleColor();
                }
            }
            ImGui::EndChild();

            // Show output history

            // Text input for command typing
            if (ImGui::InputText("Command", &inputField, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                Log("> " + inputField);    // Log the input
                ExecuteCommand(inputField);  // Process the command
                inputField.clear();
            }
        }

        ImGui::End();
    }

    void Console::Log(const std::string& message) { outputHistory.push_back(message); }

    void Console::ToggleConsole(bool isOpened)
    {
        isConsoleOpened = isOpened;
    }

    void Console::ToggleConsole()
    {
        isConsoleOpened = !isConsoleOpened;
    }
}
