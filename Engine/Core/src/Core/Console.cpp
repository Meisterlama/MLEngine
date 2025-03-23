//
// Created by Lama on 04/02/2025.
//
#include "Core/Console.h"

#include <imgui.h>

#include "Core/ImGUIIntegration.h"

namespace MLEngine {
    Console::Console() {
        RegisterCommand("clear", "Clears the console", [&]() {
            outputHistory.clear();
        });
        RegisterCommand("help", "Display all commands with their description", [&]() {
            Log("Available commands:");
            for (const auto &command: commands) {
                Log("- " + command.first + ": " + commandsDescription[command.first]);
            }
        });
    }

    bool Console::ExecuteCommand(const std::string &command) {
        if (const auto it = commands.find(command); it != commands.end()) {
            it->second(); // Execute command function
            return true;
        }
        Log("ERROR: Unknown command " + command);
        return false;
    }

    void Console::RegisterCommand(const std::string &name, const std::string &description,
                                  std::function<void()> commandFunc) {
        commands[name] = move(commandFunc);
        commandsDescription[name] = description;
    }

    void Console::RenderConsole() {
        if (!isConsoleOpened) return;
        if (ImGui::Begin("Console", &isConsoleOpened)) {
            if (ImGui::BeginChild("ConsoleOutput", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false,
                                  ImGuiWindowFlags_HorizontalScrollbar)
            ) {
                for (const std::string &log: outputHistory) {
                    ImVec4 logColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Default: White

                    // Change log color based on message type
                    if (log.rfind("ERROR:", 0) == 0) logColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red for errors
                    else if (log.rfind("WARNING:", 0) == 0)
                        logColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow for warnings

                    ImGui::PushStyleColor(ImGuiCol_Text, logColor);
                    ImGui::TextUnformatted(log.c_str());
                    ImGui::PopStyleColor();
                }
            }
            ImGui::EndChild();

            // Show output history

            // Text input for command typing
            if (ImGui::InputText("Command", &inputField, ImGuiInputTextFlags_EnterReturnsTrue)) {
                Log("> " + inputField); // Log the input
                ExecuteCommand(inputField); // Process the command
                inputField.clear();
            }
        }

        ImGui::End();
    }

    void Console::Log(const std::string &message) { outputHistory.push_back(message); }

    void Console::ToggleConsole(bool isOpened) {
        isConsoleOpened = isOpened;
    }

    void Console::ToggleConsole() {
        isConsoleOpened = !isConsoleOpened;
    }
}
