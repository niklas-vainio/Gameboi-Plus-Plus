/**
 * Entry point for the frontend of the emulator, which manages graphics, audio,
 * and user inputs.
 *
 * @author Niklas Vainio
 * @date   2026-01-26
 */

#include "frontend/App.hpp"
#include "common/logging.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>

/**
 * Helper macro to evaluate \p `expr` and log an error if the result failed.
 */
#define AbortOnSdlError(expr)                                                  \
    [&]()                                                                      \
    {                                                                          \
        const auto result = expr;                                              \
        if (!result)                                                           \
        {                                                                      \
            LogError("Call %s failed: %s\n", #expr, SDL_GetError());           \
            SDL_Quit();                                                        \
            std::exit(1);                                                      \
        }                                                                      \
        return result;                                                         \
    }();

namespace Gbpp::Frontend
{

bool App::init()
{
    /*
     * Get SDL version.
     */
    const int v = SDL_GetVersion();
    const int maj = SDL_VERSIONNUM_MAJOR(v);
    const int min = SDL_VERSIONNUM_MINOR(v);
    const int pat = SDL_VERSIONNUM_MICRO(v);
    LogDebug("SDL version: %d.%d.%d", maj, min, pat);

    /*
     * Create window and renderer.
     */
    AbortOnSdlError(SDL_Init(SDL_INIT_VIDEO));
    window = AbortOnSdlError(SDL_CreateWindow("SDL3 Hello", 800, 450, 0));
    renderer = AbortOnSdlError(SDL_CreateRenderer(window, nullptr));

    start_time = SDL_GetTicks();

    return true;
}

bool App::run_frame()
{
    auto running = true;

    /*
     * Poll events.
     */
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            running = false;
        }
    }

    /*
     * Color screen based on elapsed time.
     */
    const float t = (SDL_GetTicks() - start_time) / 1000.0f;

    auto to_u8 = [](float x)
    {
        // x expected in [0,1]
        int v = (int)(x * 255.0f + 0.5f);
        if (v < 0)
            v = 0;
        if (v > 255)
            v = 255;
        return (uint8_t)v;
    };

    const uint8_t r = to_u8(0.5f + 0.5f * std::sinf(t * 1.0f));
    const uint8_t g = to_u8(0.5f + 0.5f * std::sinf(t * 1.3f + 2.0f));
    const uint8_t b = to_u8(0.5f + 0.5f * std::sinf(t * 1.7f + 4.0f));

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
}

} // namespace Gbpp::Frontend