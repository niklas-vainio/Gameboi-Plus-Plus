/**
 * Collection of utility functions for rendering in SDL.
 *
 * @author Niklas Vainio
 * @date 2026-01-30
 */

#pragma once

#include "context.hpp"
#include <SDL3/SDL.h>

namespace Gbpp::Frontend::SDL
{

/**
 * Define some global color constants
 */
inline constexpr SDL_Color RED{255, 0, 0, 255};
inline constexpr SDL_Color GREEN{0, 255, 0, 255};
inline constexpr SDL_Color BLUE{0, 0, 255, 255};
inline constexpr SDL_Color WHITE{255, 255, 255, 255};
inline constexpr SDL_Color BLACK{0, 0, 0, 25};

/**
 * Fill the screen with a given color.
 *
 * @param[in] context   Current SDL context
 * @param[in] color     Color to fill the screen with
 */
void fill_screen(Context &context, SDL_Color color);

/**
 * Update the contents of the screen.
 *
 * @param[in] context   Current SDL context
 */
void show(Context &context);

} // namespace Gbpp::Frontend::SDL