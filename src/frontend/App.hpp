/**
 * Entry point for the frontend of the emulator, which manages graphics, audio,
 * and user inputs.
 *
 * @author Niklas Vainio
 * @date   2026-01-26
 */

#pragma once

#include "sdl/context.hpp"
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
    /**
     * Name of the window.
     */
    inline static const std::string window_title = "gameboi++";

    /**
     * Screen dimensions.
     */
    static constexpr auto screen_width{1200u};
    static constexpr auto screen_height{576u};

    /**
     * Framerate (set by Game Boy hardware)
     */
    static constexpr auto framerate{59.7275005696};

    /**
     * Active SDL context.
     */
    SDL::Context sdl_context{};

    /**
     * Number of frames processed.
     */
    uint64_t frame_count{};
};

} // namespace Gbpp::Frontend