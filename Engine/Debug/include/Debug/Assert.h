//
// Created by lama on 27/03/25.
//
#pragma once
#include "Debug/Debugger.h"

#define ML_ASSERT(condition, ...) do {if (!(condition)) { MLLogFatal("ASSERTION FAILED: {1} ({0})", #condition, __VA_ARGS__); ML_DEBUGBREAK(); }} while (false)
#define ML_STATIC_ASSERT(condition, ...) static_assert(condition, #condition)
