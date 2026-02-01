/**
 * Entry point for the frontend of the emulator, which manages graphics, audio,
 * and user inputs.
 *
 * @author Niklas Vainio
 * @date   2026-01-26
 */

#include "App.hpp"
#include "Font.hpp"
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
     * Print out SDL version.
     */
    const auto version = SDL::get_version();
    LogDebug(
        "SDL version: %d.%d.%d", version.major, version.minor, version.patch);

    /*
     * Initialize SDL context.
     */
    sdl_context = SDL::init(window_title,
                            screen_width,
                            screen_height,
                            0,
                            "GameBoy.ttf",
                            Font::size_map);

    return true;
}

bool App::run_frame()
{
    const auto frame_start = SDL::get_time();
    frame_count++;

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

    SDL::fill_screen(sdl_context, SDL::BLACK);

    SDL::fill_rect(
        sdl_context, {.x = 0, .y = 0, .h = 576, .w = 640}, SDL::BLUE);

    SDL::fill_rect(sdl_context,
                   {.x = screen_width - 256, .y = 0, .w = 256, .h = 256},
                   SDL::WHITE);

    SDL::draw_text(sdl_context,
                   "Extra Small Text here owo",
                   {20.0, 20.0},
                   SDL::WHITE,
                   Font::EXTRA_SMALL);

    SDL::draw_text(sdl_context,
                   "Small Text here: 34fa",
                   {20.0, 40.0},
                   SDL::WHITE,
                   Font::SMALL);

    SDL::draw_text(sdl_context,
                   "Medium Text here",
                   {20.0, 70.0},
                   SDL::WHITE,
                   Font::MEDIUM);

    SDL::draw_text(
        sdl_context, "Large text here", {20.0, 120.0}, SDL::WHITE, Font::LARGE);

    SDL::show(sdl_context);

    /*
     * Delay for required framerate.
     */
    SDL::delay_for_fps(frame_start, framerate);

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