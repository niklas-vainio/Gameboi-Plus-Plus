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
    AbortIfNot(Sdl::init(sdl_context,
                         window_title,
                         Graphics::Layout::screen_width,
                         Graphics::Layout::screen_height,
                         0u,
                         Font::font_file,
                         Font::size_map),
               false);

    /**
     * Initialize dynamic textures.
     */
    memory_viewer_texture.init(sdl_context,
                               MemoryViewerPixelBuffer::width,
                               MemoryViewerPixelBuffer::height);

    /*
     * Make sure control state flags are correctly initialied
     */
    control_state.app_running = true;

    /*
     * Print out log message with SDL version.
     */
    const auto version = Sdl::get_version();
    LogInfo(ANSI_CYAN "SDL Frontend App Initialized! (SDL%d.%d.%d)",
            version.major,
            version.minor,
            version.patch);
    return true;
}

void App::start_frame()
{
    frame_start = Sdl::get_time();
    frame_count++;
}

void App::handle_inputs()
{
    /*
     * Clear all control state flags that look for key press events.
     */
    control_state.run_single_instruction = false;

    Sdl::handle_events([this](const auto &event) { handle_sdl_event(event); });
}

void App::draw_frame(const EmulatorDebugInfo &debug_info)
{
    /*
     * Populate runtime textures with data from the emulator.
     */
    {
        auto pixels = memory_viewer_texture.lock();

        for (auto x = 0; x < 256; x++)
        {
            for (auto y = 0; y < 256; y++)
            {
                const auto value = debug_info.memory_viewer_pixel_buffer(x, y);
                pixels(x, y) = {.r = value, .g = value, .b = value, .a = 255};
            }
        }
    }

    Graphics::draw_frame(sdl_context, memory_viewer_texture, debug_info);
}

void App::wait_until_frame_over()
{
    Sdl::delay_for_fps(frame_start, GameBoyConstants::framerate);
}

void App::quit()
{
    /*
     * Destroy render and window, then exit.
     */
    memory_viewer_texture.destroy();
    Sdl::quit(sdl_context);
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
            case SDLK_RETURN:
                control_state.run_single_instruction = true;
                break;
            case SDLK_SPACE:
                control_state.run_many_instructions =
                    !control_state.run_many_instructions;
                break;
        }
    }
}

} // namespace Gbpp::Frontend