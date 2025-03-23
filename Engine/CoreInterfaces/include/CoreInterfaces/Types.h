//
// Created by lama on 22/03/25.
//
#pragma once

#include <memory>

using UInt64 = std::uint64_t;
using Int64 = std::int64_t;
using UInt32 = std::uint32_t;
using Int32 = std::int32_t;
using UInt16 = std::uint16_t;
using Int16 = std::int16_t;
using UInt8 = std::uint8_t;
using Int8 = std::int8_t;

using Float32 = float;
using Float64 = double;

template<typename T>
using Handle = std::shared_ptr<T>;

template<typename T>
using ExclusiveHandle = std::unique_ptr<T>;

template<typename T, typename... Args>
Handle<T> MakeHandle(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
ExclusiveHandle<T> MakeExclusiveHandle(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}