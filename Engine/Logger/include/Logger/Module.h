//
// Created by lama on 22/03/25.
//
#pragma once

#include "CoreInterfaces/ModuleInterface.h"
#include "CoreInterfaces/Types.h"
#include "Logger/Logger.h"
#include "Logger/Preprocessor.h"

namespace MLEngine
{
    class LoggerModule : ModuleInterface
    {
    public:
        LoggerModule() : ModuleInterface(){};
        ~LoggerModule() override = default;

        void SetLevel(const LogLevel new_level) { level = new_level; }

        void SetQuiet(const bool enable) { quiet = enable; }

        void AddCallback(LogFn callback);
        void AddFile(std::string FilePath);

        void RemoveCallback(LogFn callback);;

        void ManualLog(const LogLevel level, const std::string&& message, const std::string&& file_name, const Int32&& line) const;
    private:

        std::vector<LogFn> logCallbacks{};
        std::vector<Handle<std::ofstream>> openedFiles{};
        bool quiet = false;
        LogLevel level = LogLevel::Info;
    };
}