//
// Created by lama on 22/03/25.
//
#pragma once

#include <memory>

namespace MLEngine
{
    template <typename T>
    using Handle = std::shared_ptr<T>;

    template <typename T, typename... Args>
    Handle<T> MakeHandle(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using ExclHandle = std::unique_ptr<T>;

    template <typename T, typename... Args>
    ExclHandle<T> MakeExclusiveHandle(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}
