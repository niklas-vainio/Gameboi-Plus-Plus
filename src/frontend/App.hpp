/**
 * Entry point for the frontend of the emulator, which manages graphics, audio,
 * and user inputs.
 *
 * @author Niklas Vainio
 * @date   2026-01-26
 */

#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

namespace Gbpp::Frontend
{

class App
{
public:
    /**
     * Initialize the app.
     *
     * @return True on success, false otherwise.
     */
    bool init();

    /**
     * Process a single frame.
     *
     * @return True if the app should continue running, false otherwise.
     */
    bool run_frame();

    /**
     * Exit the app.
     */
    void quit();

private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};

    uint64_t start_time{};
};

} // namespace Gbpp::Frontend