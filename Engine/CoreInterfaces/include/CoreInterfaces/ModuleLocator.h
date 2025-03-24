//
// Created by lama on 22/03/25.
//
#pragma once
#include <cassert>
#include <memory>

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
            assert(!instance); // "Module already registered"
            instance = MakeHandle<T>();
            return instance;
        }

        static constexpr Handle<T> RegisterInit()
        {
            ModuleLocator::Register()->Init();
            return instance;
        }

        static constexpr Handle<T> Get()
        {
            assert(instance && instance->IsInitialized()); // "Module not registered"
            return instance;
        }

    private:
        static Handle<T> instance;
    };

    template <typename T>
    Handle<T> ModuleLocator<T>::instance{};
}
