/**
 * Simple test for now.
 *
 * @author Niklas Vainio
 * @date   2026-01-25
 */

#include <SDL3/SDL.h>
#include <cmath>
#include <cstdio>

int main(int, char **)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // SDL3: SDL_GetVersion() returns an int (encoded version)
    const int v = SDL_GetVersion();
    const int maj = SDL_VERSIONNUM_MAJOR(v);
    const int min = SDL_VERSIONNUM_MINOR(v);
    const int pat = SDL_VERSIONNUM_MICRO(v);
    std::printf("SDL version: %d.%d.%d\n", maj, min, pat);

    SDL_Window *window = SDL_CreateWindow("SDL3 Hello", 800, 450, 0);
    if (!window)
    {
        std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer for the window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        std::fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    const Uint64 start = SDL_GetTicks(); // ms since SDL_Init

    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        // t in seconds
        const float t = (SDL_GetTicks() - start) / 1000.0f;

        // Smooth color cycling via sine waves
        auto to_u8 = [](float x) -> Uint8
        {
            // x expected in [0,1]
            int v = (int)(x * 255.0f + 0.5f);
            if (v < 0)
                v = 0;
            if (v > 255)
                v = 255;
            return (Uint8)v;
        };

        const Uint8 r = to_u8(0.5f + 0.5f * std::sinf(t * 1.0f));
        const Uint8 g = to_u8(0.5f + 0.5f * std::sinf(t * 1.3f + 2.0f));
        const Uint8 b = to_u8(0.5f + 0.5f * std::sinf(t * 1.7f + 4.0f));

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        // Cap to ~60fps
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
