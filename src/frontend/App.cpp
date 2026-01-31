/**
 * Entry point for the frontend of the emulator, which manages graphics, audio,
 * and user inputs.
 *
 * @author Niklas Vainio
 * @date   2026-01-26
 */

#include "App.hpp"
#include "common/logging.hpp"
#include "sdl/abort.hpp"
#include "sdl/events.hpp"
#include "sdl/graphics.hpp"
#include "sdl/time.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace Gbpp::Frontend
{

bool App::init()
{
    /*
     * Get SDL version.
     */
    const auto version = SDL::get_version();
    LogDebug(
        "SDL version: %d.%d.%d", version.major, version.minor, version.patch);

    /*
     * Initialize SDL context
     */
    sdl_context = SDL::init(window_title, screen_width, screen_height, 0);

    // start_time = SDL_GetTicks();

    return true;
}

bool App::run_frame()
{
    auto running = true;

    SDL::handle_events(
        [&](const SDL_Event &event)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.key == SDLK_SPACE)
                {
                    LogWarning("Don't you dare press space :O");
                }
            }
        });

    /*
     * Color screen based on elapsed time.
     */
    // const float t = (SDL_GetTicks() - start_time) / 1000.0f;

    // auto to_u8 = [](float x)
    // {
    //     // x expected in [0,1]
    //     int v = (int)(x * 255.0f + 0.5f);
    //     if (v < 0)
    //         v = 0;
    //     if (v > 255)
    //         v = 255;
    //     return (uint8_t)v;
    // };

    // const uint8_t r = to_u8(0.5f + 0.5f * std::sinf(t * 1.0f));
    // const uint8_t g = to_u8(0.5f + 0.5f * std::sinf(t * 1.3f + 2.0f));
    // const uint8_t b = to_u8(0.5f + 0.5f * std::sinf(t * 1.7f + 4.0f));

    SDL::fill_screen(sdl_context, SDL::BLACK);

    SDL_SetRenderDrawColor(sdl_context.renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(sdl_context.renderer, 200, 200, "HELLO");

    SDL::show(sdl_context);

    /*
     * Delay to 60 fps.
     */
    SDL_Delay(16);

    return running;
}

void App::quit()
{
    /*
     * Destroy render and window, then exit.
     */
    SDL::quit(sdl_context);
    return;
}

} // namespace Gbpp::Frontend