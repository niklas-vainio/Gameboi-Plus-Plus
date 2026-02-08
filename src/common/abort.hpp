/**
 * Helper macros for logging errors.
 *
 * @author Niklas Vainio
 * @date   2026-02-07
 */

#pragma once

#include "common/logging.hpp"
#include <SDL3/SDL.h>

/**
 * Internal implementation for an abort action. Uses variadic arguments
 * as logging specifiers and returns \p `retval` .
 */
#define AbortImpl(retval, ...)                                                 \
    LogError(__VA_ARGS__);                                                     \
    return retval;

/**
 * Raise an error error and return \p `retval` . Any extra arguments are passed
 * to a LogError call, so they may contain a string, or format specifier with
 * values.
 */
#define Abort(retval, ...)                                                     \
    do                                                                         \
    {                                                                          \
        AbortImpl(retval __VA_OPT__(, ) __VA_ARGS__)                           \
    } while (0)

/**
 * Abort if \p `expr` evaluates to true.
 */
#define AbortIf(expr, retval, ...)                                             \
    do                                                                         \
    {                                                                          \
        if ((expr))                                                            \
        {                                                                      \
            AbortImpl(retval __VA_OPT__(, ) __VA_ARGS__)                       \
        }                                                                      \
    } while (0)

/**
 * Abort if \p `expr` evaluates to false.
 */
#define AbortIfNot(expr, retval, ...)                                          \
    do                                                                         \
    {                                                                          \
        if (!(expr))                                                           \
        {                                                                      \
            AbortImpl(retval __VA_OPT__(, ) __VA_ARGS__)                       \
        }                                                                      \
    } while (0)