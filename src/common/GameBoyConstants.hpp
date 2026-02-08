/**
 * File containing gameboy hardware constants used throughout the emulator.
 *
 * @author Niklas Vainio
 * @date   2026-02-01
 */

#pragma once

#include <cstdint>

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
 * Game Boy framerate [fps].
 */
inline constexpr auto framerate = 59.7275005696;

/**
 * Game Boy clock speed [Hz].
 */
inline constexpr auto clock_speed = 4.194304e6;

/**
 * Number of clock cycles per frame.
 */
inline constexpr auto clock_cycles_per_frame =
    static_cast<uint32_t>(clock_speed / framerate);

} // namespace Gbpp::GameBoyConstants