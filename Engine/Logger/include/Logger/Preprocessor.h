//
// Created by lama on 22/03/25.
//
#pragma once

#include "fmt/core.h"
#include "CoreInterfaces/ModuleLocator.h"

#define ML_STRINGIFY(x) #x
#define ML_EXPAND(x) x
#define ML_EXPAND_ARGS(...) , ##__VA_ARGS__
#define ML_FMT(formatString, ...) fmt::format(formatString ML_EXPAND_ARGS(__VA_ARGS__))
#define INTERNAL_ML_LOG(level, fmt, ...) ::MLEngine::ModuleLocator<LoggerModule>::Get()->ManualLog(::MLEngine::LogLevel::level, ML_FMT(fmt, __VA_ARGS__), __FILE__, __LINE__)

#ifdef ML_DEBUG

#define MLLogTrace(fmt, ...) INTERNAL_ML_LOG(Trace, fmt, __VA_ARGS__)
#define MLLogDebug(fmt, ...) INTERNAL_ML_LOG(Debug, fmt, __VA_ARGS__)
#define MLLogInfo(fmt, ...) INTERNAL_ML_LOG(Info, fmt, __VA_ARGS__)
#define MLLogWarn(fmt, ...) INTERNAL_ML_LOG(Warning, fmt, __VA_ARGS__)
#define MLLogError(fmt, ...) INTERNAL_ML_LOG(Error, fmt, __VA_ARGS__)
#define MLLogFatal(fmt, ...) INTERNAL_ML_LOG(Critical, fmt, __VA_ARGS__)

#else

#define MLLogTrace(...)
#define MLLogDebug(...)
#define MLLogInfo(...)
#define MLLogWarn(...)
#define MLLogError(...)
#define MLLogFatal(...)

#endif
