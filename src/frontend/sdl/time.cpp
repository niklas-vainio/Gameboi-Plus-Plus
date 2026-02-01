/**
 * Collection of utility functions to handle timing in SDL.
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#include "time.hpp"

namespace Gbpp::Frontend::SDL
{

Time get_time()
{
    return SDL_GetTicksNS();
}

Time advance(const Time time, const uint64_t interval_ns)
{
    return time + interval_ns;
}

void delay_until(const Time time)
{
    const auto current_time = get_time();

    if (current_time >= time)
    {
        return;
    }

    /*
     * Approximate delay, subject to OS sleeping.
     *
     * TODO: Investigate VSYNC/more precise frame timing
     */
    SDL_DelayNS(time - get_time());
}

void delay_for_fps(const Time frame_start, const double fps)
{
    const auto frame_end =
        advance(frame_start, static_cast<uint64_t>(1e9 / fps));

    delay_until(frame_end);
}

} // namespace Gbpp::Frontend::SDL