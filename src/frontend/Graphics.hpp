/**
 * Functions for rendering the emulator screen and UI.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include "App.hpp"
#include "common/EmulatorDebugInfo.hpp"
#include "sdl/graphics.hpp"

namespace Gbpp::Frontend::Graphics
{

inline constexpr auto screen_width = App::screen_width;
inline constexpr auto screen_height = App::screen_height;

/**
 * Draw the current frame to the screen.
 *
 * @param[in] sdl_context   Current SDL context.
 * @param[in] debug_info    Current debug info from the backend.
 */
void draw_frame(SDL::Context &sdl_context, const EmulatorDebugInfo &debug_info);

} // namespace Gbpp::Frontend::Graphics