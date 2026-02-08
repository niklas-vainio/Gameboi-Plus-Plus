/**
 * Entry point for the frontend of the emulator, which manages graphics, audio,
 * and user inputs.
 *
 * @author Niklas Vainio
 * @date   2026-01-26
 */

#pragma once

#include "common/Control.hpp"
#include "common/DebugInfo.hpp"
#include "common/GameBoyConstants.hpp"
#include "sdl/context.hpp"
#include "sdl/time.hpp"
#include <cstdint>
#include <string>

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
     * Start the current frame.
     */
    void start_frame();

    /**
     * Handle user inputs for the current frame.
     */
    void handle_inputs();

    /**
     * Render the current frame to the screen.
     *
     * @param[in] debug_info    Current debug info from the backend.
     */
    void draw_frame(const EmulatorDebugInfo &debug_info);

    /**
     * Waits until the frame is over. Requires start_frame to have been called
     * previously so the starting timestamp can be logged.
     */
    void wait_until_frame_over();

    /**
     * Exit the app.
     */
    void quit();

    /**
     * @return Structure containing the current user inputs.
     */
    const ControlState &get_control_state() const
    {
        return control_state;
    };

private:
    /**
     * Main function for handling SDL events.
     */
    void handle_sdl_event(const SDL_Event &event);

    /**
     * Name of the window.
     */
    static constexpr std::string window_title = "gameboi++";

    /**
     * Active SDL context.
     */
    Sdl::Context sdl_context{};

    /**
     * The current set of user inputs, updated each frame.
     */
    ControlState control_state{};

    /**
     * Timestamp of the start of the furrent frame.
     */
    Sdl::Time frame_start{};

    /**
     * Number of frames processed.
     */
    uint64_t frame_count{};
};

} // namespace Gbpp::Frontend