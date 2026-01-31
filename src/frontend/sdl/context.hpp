/**
 * Collection of utility functions to handle interacting with the SDL layer
 *
 * @author Niklas Vainio
 * @date 2026-01-30
 */

#pragma once

#include <SDL3/SDL.h>
#include <cstdint>
#include <string>

namespace Gbpp::Frontend::SDL
{

/**
 * Struct representing the SDL version.
 */
struct Version
{
    uint32_t major{};
    uint32_t minor{};
    uint32_t patch{};
};

/**
 * @return The currently active SDL version
 */
Version get_version();

/**
 * Collection of objects defining the currently open SDL session.
 */
struct Context
{
    SDL_Window *window{};
    SDL_Renderer *renderer{};
};

/**
 * Initialize SDL, returning a Context struct.
 *
 * @param[in] window_title  Title for the window.
 * @param[in] screen_width  Width of the screen, in pixels.
 * @param[in] screen_height Height of the screen, in pixels.
 * @param[in] flags         Window settings.
 */
Context init(const std::string &window_title,
             const uint32_t screen_width,
             const uint32_t screen_height,
             const uint64_t flags);

/**
 * Destroy the currently running SDL instance.
 *
 * @param[in] context   Current SDL context.
 */
void quit(Context &context);

} // namespace Gbpp::Frontend::SDL