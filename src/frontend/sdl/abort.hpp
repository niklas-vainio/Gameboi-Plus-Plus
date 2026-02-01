/**
 * Helper macros for handling and logging SDL errors.
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#pragma once

#include "common/logging.hpp"
#include <SDL3/SDL.h>

/**
 * Eevaluate \p `expr` and log an error if the result failed.
 */
#define AbortOnSdlError(expr)                                                  \
    [&]()                                                                      \
    {                                                                          \
        const auto result = expr;                                              \
        if (!result)                                                           \
        {                                                                      \
            LogError("Call %s failed: %s\n", #expr, SDL_GetError());           \
            SDL_Quit();                                                        \
            std::exit(1);                                                      \
        }                                                                      \
        return result;                                                         \
    }();