/**
 * Functions for rendering the emulator screen and UI.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include "App.hpp"
#include "sdl/graphics.hpp"

namespace Gbpp::Frontend::Graphics
{

inline constexpr auto screen_width = App::screen_width;
inline constexpr auto screen_height = App::screen_height;

/**
 * Draw the current frame to the screen.
 *
 * @param[in] sdl_context   Current SDL context.
 */
void draw_frame(SDL::Context &sdl_context);

} // namespace Gbpp::Frontend::Graphics