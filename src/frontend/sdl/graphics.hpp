/**
 * Collection of utility functions for rendering in SDL.
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#pragma once

#include "context.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace Gbpp::Frontend::SDL
{

/**
 * Struct to store a screen position with coordinates of any type (typically an
 * int/float).
 */
template <typename T>
struct Position
{
    T x{};
    T y{};
};

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
void fill_screen(Context &context, const SDL_Color color);

/**
 * Draw a filled rectangle to the screen.
 *
 * @param[in] context   Current SDL context
 * @param[in] rect      Rectangle to fill
 * @param[in] color     Color to fill with.
 */
void fill_rect(Context &context, const SDL_FRect rect, const SDL_Color color);

/**
 * Render text to the screen.
 *
 * @param[in] context   Current SDL context
 * @param[in] text      Text to render
 * @param[in] position  Positon to render the text
 * @param[in] color     Text color
 * @param[in] font_size Font size (index into sizes loaded by context)
 */
void draw_text(Context &context,
               const std::string &text,
               const Position<float> position,
               const SDL_Color color,
               const uint32_t font_size);

/**
 * Update the contents of the screen.
 *
 * @param[in] context   Current SDL context
 */
void show(Context &context);

} // namespace Gbpp::Frontend::SDL