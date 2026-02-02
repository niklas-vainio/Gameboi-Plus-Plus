/**
 * Functions for rendering the emulator screen and UI.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include "App.hpp"
#include "common/DebugInfo.hpp"
#include "common/GameBoyConstants.hpp"
#include "sdl/graphics.hpp"

namespace Gbpp::Frontend::Graphics
{

/**
 * Constants defining fixed screen positions.
 */
namespace Layout
{

/**
 * Size of a Game Boy pixel in the emulator display.
 */
inline constexpr auto pixel_scale = 4u;

/**
 * Size of the Game Boy screen viewer.
 */
inline constexpr auto game_boy_viwer_width =
    pixel_scale * GameBoyConstants::screen_width;
inline constexpr auto game_boy_viwer_height =
    pixel_scale * GameBoyConstants::screen_height;

/**
 * Width of the debug panel (in pixels).
 */
inline constexpr auto debug_panel_width = 500u;

/**
 * Overall screen dimensions.
 */
inline constexpr auto screen_width = game_boy_viwer_width + debug_panel_width;
inline constexpr auto screen_height = game_boy_viwer_height;

inline constexpr auto debug_panel_start = screen_width - debug_panel_width;

/**
 * Standard UI padding to use
 */
inline constexpr auto padding = 10u;

} // namespace Layout

/**
 * Draw the current frame to the screen.
 *
 * @param[in] sdl_context   Current SDL context.
 * @param[in] debug_info    Current debug info from the backend.
 */
void draw_frame(SDL::Context &sdl_context, const EmulatorDebugInfo &debug_info);

/**
 * Draw the current status of the CPU
 *
 * @param[in] sdl_context   Current SDL context.
 * @param[in] cpu           CPU debug info from the backend
 */
void draw_cpu_status(SDL::Context &sdl_context, const CpuDebugInfo &cpu);

} // namespace Gbpp::Frontend::Graphics