/**
 * Collection of utility functions to manage events in SDL
 *
 * @author Niklas Vainio
 * @date 2026-01-30
 */

#pragma once

#include <SDL3/SDL.h>

namespace Gbpp::Frontend::SDL
{

/**
 * Handle all SDL events, passing each one to the provided callback.
 *
 * @param[in] callback  Function to call on each SDL event.
 */
template <typename T>
void handle_events(const T &callback)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        callback(e);
    }
};

} // namespace Gbpp::Frontent
