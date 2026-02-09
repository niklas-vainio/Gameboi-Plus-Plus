/**
 * Collection of utility functions for rendering in SDL.
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#pragma once

#include "context.hpp"
#include "runtime_texture.hpp"
#include "types.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace Gbpp::Frontend::Sdl
{

/**
 * Define some global color constants
 */
inline constexpr Color RED{255, 0, 0, 255};
inline constexpr Color GREEN{0, 255, 0, 255};
inline constexpr Color BLUE{0, 0, 255, 255};
inline constexpr Color YELLOW{255, 255, 0, 255};
inline constexpr Color MAGENTA{255, 0, 255, 255};
inline constexpr Color CYAN{0, 255, 255, 255};
inline constexpr Color WHITE{255, 255, 255, 255};
inline constexpr Color BLACK{0, 0, 0, 25};

/**
 * Fill the screen with a given color.
 *
 * @param[in] context   Current SDL context
 * @param[in] color     Color to fill the screen with
 */
void fill_screen(Context &context, const Color color);

/**
 * Draw a filled rectangle to the screen.
 *
 * @param[in] context   Current SDL context
 * @param[in] rect      Rectangle to fill
 * @param[in] color     Color to fill with.
 */
void fill_rect(Context &context, const Rect<float> rect, const Color color);

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
               const Color color,
               const uint32_t font_size);

/**
 * Draw a runtime texture to the screen.
 *
 * @param[in] context   Current SDL context
 * @param[in] texture   Texture to render
 * @param[in] rect      Area on the screen to render
 */
void draw_runtime_texture(Context &context,
                          RuntimeTexture &texture,
                          const Rect<float> rect);

/**
 * Update the contents of the screen.
 *
 * @param[in] context   Current SDL context
 */
void show(Context &context);

} // namespace Gbpp::Frontend::Sdl