#pragma once

#include <csignal>

#define RCheck(Condition) \
    (Condition ||        \
    []()                 \
    {                    \
        raise(SIGTRAP);  \
        return false;    \
    }())

#define RCheckReturn(Condition, ...)       \
    if (!Check(Condition))                \
        return __VA_ARGS__;               \
    else                                  \
        volatile auto __stub = ((void*)0)

#define RCheckContinue(Condition)          \
    if (!Check(Condition))                \
        continue;                         \
    else                                  \
        volatile auto __stub = ((void*)0)

#define RCheckBreak(Condition)             \
    if (!Check(Condition))                \
        break;                            \
    else                                  \
        volatile auto __stub = ((void*)0)