//
// Created by lama on 22/03/25.
//
#pragma once
#include <memory>
#include <cassert>

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
            //TODO: Prevent/warn if multiple registration
            instance = MakeHandle<T>();
            return instance;
        }

        static constexpr Handle<T> Get()
        {
            assert(instance); // "Module not registered"
            return instance;
        }

    private:
        static Handle<T> instance;
    };

    template <typename T>
    Handle<T> ModuleLocator<T>::instance{};
}
