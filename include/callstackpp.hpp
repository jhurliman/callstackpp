#pragma once

// The callstackpp namespace.
//
// callstackpp pretty prints stack traces on unexpected program termination

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wundef"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif

#include "backward/backward.hpp"

#if defined(__clang__)
#pragma clang diagnostic push
#else
#pragma GCC diagnostic pop
#endif

#include "callstackpp/callstack.hpp"
#include "callstackpp/version.hpp"
