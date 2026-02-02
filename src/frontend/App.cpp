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

#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace Gbpp::Frontend
{

bool App::init()
{
    /*
     * Initialize SDL context.
     */
    sdl_context = SDL::init(window_title,
                            Graphics::Layout::screen_width,
                            Graphics::Layout::screen_height,
                            0u,
                            Font::font_file,
                            Font::size_map);

    /*
     * Make sure control state flags are correctly initialied
     */
    control_state.app_running = true;

    /*
     * Print out log message with SDL version.
     */
    const auto version = SDL::get_version();
    LogInfo(ANSI_CYAN "SDL Frontend App Initialized! (SDL%d.%d.%d)",
            version.major,
            version.minor,
            version.patch);
    return true;
}

void App::start_frame()
{
    frame_start = SDL::get_time();
    frame_count++;
}

void App::handle_inputs()
{
    /*
     * Clear all control state flags that look for key press events.
     */
    control_state.run_cpu_instruction = false;

    SDL::handle_events([this](const auto &event) { handle_sdl_event(event); });
}

void App::draw_frame(const EmulatorDebugInfo &debug_info)
{
    Graphics::draw_frame(sdl_context, debug_info);
}

void App::wait_until_frame_over()
{
    SDL::delay_for_fps(frame_start, GameBoyConstants::framerate);
}

void App::quit()
{
    /*
     * Destroy render and window, then exit.
     */
    SDL::quit(sdl_context);
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
    }
}

} // namespace Gbpp::Frontend