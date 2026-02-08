/**
 * Helper macros for handling and logging SDL errors.
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#pragma once

#include "common/abort.hpp"
#include "common/logging.hpp"
#include <SDL3/SDL.h>

/**
 * If \p `expr` evaluates to false, i.e. it is the result of a failed SDL call,
 * abort with a descriptive error message.
 */
#define AbortOnSDLError(expr)                                                  \
    do                                                                         \
    {                                                                          \
        if (!(expr))                                                           \
        {                                                                      \
            AbortImpl(false, "SDL Error: %s\n", SDL_GetError());               \
        }                                                                      \
    } while (0)