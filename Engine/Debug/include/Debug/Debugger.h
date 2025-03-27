//
// Created by lama on 27/03/25.
//
#pragma once

namespace MLEngine
{
    bool IsDebuggerAttached();
}

#if ML_LINUX
    #define ML_DEBUGBREAK() if (::MLEngine::IsDebuggerAttached()) { __asm__ volatile("int $0x03"); }
#elif ML_WINDOWS
    #define ML_DEBUGBREAK() if (::MLEngine::IsDebuggerAttached()) { __debugbreak(); }
#endif