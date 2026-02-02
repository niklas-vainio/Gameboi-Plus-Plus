/**
 * File containing gameboy hardware constants used throughout the emulator.
 *
 * @author Niklas Vainio
 * @date   2026-02-01
 */

#pragma once

namespace Gbpp::GameBoyConstants
{

/**
 * Game Boy screen width (in pixels)
 */
inline constexpr auto screen_width = 160u;

/**
 * Game Boy screen height (in pixels)
 */
inline constexpr auto screen_height = 160u;

/**
 * Game Boy framerate
 */
inline constexpr auto framerate = 59.7275005696;

} // namespace Gbpp::GameBoyConstants