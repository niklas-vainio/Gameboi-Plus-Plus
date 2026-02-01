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

    /*
     * Make sure control state flags are correctly initialied
     */
    control_state.app_running = true;

    return true;
}

void App::start_frame()
{
    frame_start = SDL::get_time();
    frame_count++;
}

const ControlState &App::handle_inputs()
{
    /*
     * Clear all control state flags that look for key press events.
     */
    control_state.run_cpu_instruction = false;

    SDL::handle_events([this](const auto &event) { handle_sdl_event(event); });

    return control_state;
}

void App::render_frame()
{
    Graphics::draw_frame(sdl_context);
}

void App::wait_until_frame_over()
{
    SDL::delay_for_fps(frame_start, framerate);
}

void App::handle_sdl_event(const SDL_Event &event)
{
    /*
     * Handle quitting the app.
     */
    if (event.type == SDL_EVENT_QUIT)
    {
        control_state.app_running = false;
    }

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        /*
         * Handle key press events.
         */
        switch (event.key.key)
        {
            case SDLK_SPACE:
                control_state.run_cpu_instruction = true;
                break;
        }

        LogInfo("User pressed key: %x", event.key.key);
    }
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