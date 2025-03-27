//
// Created by lama on 27/03/25.
//
#include "Debug/Debugger.h"

#include <fstream>

#include "Debug/Logger.h"

#if ML_LINUX
#include <sys/ptrace.h>
#elif ML_WINDOWS
#include <windows.h>
#endif

namespace MLEngine
{
    bool IsDebuggerAttached()
    {
#if ML_LINUX
        // If /proc/self/status contains a TracerPid != 0, it means that the process is being traced/debugged
        auto stream = std::ifstream("/proc/self/status");
        if (!stream.is_open())
        {
            MLLogError("Failed to open /proc/self/status");
            return false;
        }

        for (std::string line; std::getline(stream, line);)
        {
            if (line.find("TracerPid:") != std::string::npos)
            {
                const int tracerPid = std::atoi(line.substr(line.find(':') + 1).c_str());
                return tracerPid ? true : false;
            }
        }
        return false;

#elif ML_WINDOWS
        return ::IsDebuggerPresent();
#endif
    }
}
