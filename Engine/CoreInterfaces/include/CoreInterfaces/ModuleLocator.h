//
// Created by lama on 22/03/25.
//
#pragma once
#include "ModuleInterface.h"
#include "CoreInterfaces/Types.h"

namespace MLEngine
{
    template <typename T>
    class ModuleLocator
    {
        static_assert(std::is_base_of_v<ModuleInterface, T>,
                      "T must derive from ModuleInterface");

    public:
        static constexpr Handle<T> Register()
        {
            ML_ASSERT(!IsInitialized(), "Module already registered");
            instance = MakeHandle<T>();
            return instance;
        }

        static constexpr Handle<T> RegisterInit()
        {
            ModuleLocator::Register()->Init();
            return instance;
        }

        static constexpr void Unregister()
        {
            if (IsInitialized())
            {
                instance->Shutdown();
            }
            instance = nullptr;
        }

        static constexpr Handle<T> Get()
        {
            ML_ASSERT(IsInitialized(), "Module not registered");
            return instance;
        }

        static constexpr bool IsInitialized()
        {
            return instance && instance->IsInitialized();
        }

    private:
        // TODO: Refactor to better manage lifetime
        // When a Module isn't properly cleaned up at the end of Engine lifetime,
        // it may be destructed at random time causing UB (currently segfault because logger is destroyed before)
        static Handle<T> instance;
    };

    template <typename T>
    Handle<T> ModuleLocator<T>::instance{};
}
