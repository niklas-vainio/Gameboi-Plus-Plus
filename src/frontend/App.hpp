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
    inline static const std::string window_title = "Gameboi-Plus-Plus";

    /**
     * Screen dimensions.
     */
    static constexpr auto screen_width{800u};
    static constexpr auto screen_height{600u};

    /**
     * Active SDL context.
     */
    SDL::Context sdl_context{};
};

} // namespace Gbpp::Frontend