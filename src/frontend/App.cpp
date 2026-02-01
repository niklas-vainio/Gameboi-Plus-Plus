/**
 * Entry point for the frontend of the emulator, which manages graphics, audio,
 * and user inputs.
 *
 * @author Niklas Vainio
 * @date   2026-01-26
 */

#include "App.hpp"
#include "Font.hpp"
#include "Graphics.hpp"
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
                            Font::font_file,
                            Font::size_map);

    return true;
}

void App::handle_sdl_event(const SDL_Event &event)
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
}

bool App::run_frame()
{
    const auto frame_start = SDL::get_time();
    frame_count++;

    SDL::handle_events([this](const auto &event) { handle_sdl_event(event); });

    /**
     * Draw frame.
     */
    Graphics::draw_frame(sdl_context);

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