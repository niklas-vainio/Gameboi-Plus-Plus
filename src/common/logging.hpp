/**
 * Collection of macros for logging.
 *
 * @author Niklas Vainio
 * @date   2026-01-26
 */

#pragma once

#include <cstdio>

/**
 * Define macros for ANSI color codes.
 */
#define ANSI_BLACK "\e[0;30m"
#define ANSI_RED "\e[0;31m"
#define ANSI_GREEN "\e[0;32m"
#define ANSI_YELLOW "\e[0;33m"
#define ANSI_BLUE "\e[0;34m"
#define ANSI_PURPLE "\e[0;35m"
#define ANSI_CYAN "\e[0;36m"
#define ANSI_WHITE "\e[0;37m"
#define ANSI_GRAY "\e[0;90m"

/**
 * Log a formatted message with the [INFO] prefix.
 */
#define LogDebug(fmt, ...)                                                     \
    do                                                                         \
    {                                                                          \
        std::printf(ANSI_GRAY "[DEBUG] %s:%d    " fmt "\n",                    \
                    __FILE_NAME__,                                             \
                    __LINE__ __VA_OPT__(, ) __VA_ARGS__);                      \
    } while (0)

/**
 * Log a formatted message with the [INFO] prefix.
 */
#define LogInfo(fmt, ...)                                                      \
    do                                                                         \
    {                                                                          \
        std::printf(ANSI_WHITE "[INFO] %s:%d    " fmt "\n",                    \
                    __FILE_NAME__,                                             \
                    __LINE__ __VA_OPT__(, ) __VA_ARGS__);                      \
    } while (0)

/**
 * Log a formatted message with the [WARNING] prefix.
 */
#define LogWarning(fmt, ...)                                                   \
    do                                                                         \
    {                                                                          \
        std::printf(ANSI_YELLOW "[WARNING] %s:%d    " fmt "\n",                \
                    __FILE_NAME__,                                             \
                    __LINE__ __VA_OPT__(, ) __VA_ARGS__);                      \
    } while (0)

/**
 * Log a formatted message with the [ERROR] prefix.
 */
#define LogError(fmt, ...)                                                     \
    do                                                                         \
    {                                                                          \
        std::printf(ANSI_RED "[ERROR] %s:%d    " fmt "\n",                     \
                    __FILE_NAME__,                                             \
                    __LINE__ __VA_OPT__(, ) __VA_ARGS__);                      \
    } while (0)