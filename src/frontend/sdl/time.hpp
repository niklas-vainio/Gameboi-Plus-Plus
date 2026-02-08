/**
 * Collection of utility functions to handle timing in SDL.
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

namespace Gbpp::Frontend::Sdl
{

/**
 * Represents an absolute timestamp (stored internally as a number of
 * nanoseconds since SDL library initialization).
 */
using Time = uint64_t;

/**
 * @return The current monotonic timestamp.
 */
Time get_time();

/**
 * Compute the given timestamp advanced by a specified number of nanoseconds.
 *
 * @param time          Starting timestamp
 * @param interval_ns   Number of nanoseconds to advance by
 * @return The starting timestamp delayed by the specified interval.
 */
Time advance(const Time time, const uint64_t interval_ns);

/**
 * Delay until the specified timestamp.
 *
 * @param time   The timestamp to delay until
 */
void delay_until(const Time time);

/**
 * Delays for the required amoount of time to keep the FPS at the current value,
 * given the time that the frame started.
 *
 * @note get_time should be called at the start of the frame, and the result
 * passed in to frame_start.
 *
 * @param[in] frame_start   Timestamp at the start of the frame.
 * @param[in] fps           Desired FPS.
 */
void delay_for_fps(const Time frame_start, const double fps);

} // namespace Gbpp::Frontend::Sdl
