/**
 * Main class holding all app state.
 *
 * @author Niklas Vainio
 * @date   2026-01-25
 */

#include "GameboiPlusPlus.hpp"
#include "common/abort.hpp"
#include "common/logging.hpp"

namespace Gbpp
{

bool GameboiPlusPlus::go()
{
    /*
     * Initialize.
     */
    if (!init())
    {
        LogError("Failed initialization, quitting!");
        quit();
        return false;
    }

    /*
     * Run frames until we are due to exit.
     */
    while (run_frame())
    {
    }

    /*
     * Exit.
     */
    quit();
    return true;
}

bool GameboiPlusPlus::init()
{
    LogInfo("Initializing...");
    AbortIfNot(emulator.init(rom_path), false);
    AbortIfNot(app.init(), false);

    return true;
}

bool GameboiPlusPlus::run_frame()
{
    app.start_frame();

    /*
     * Handle user inputs
     */
    app.handle_inputs();
    const auto control_state = app.get_control_state();

    /*
     * Dispatch the emulator for this frame.
     */
    emulator.emulate_frame(control_state);

    /*
     * Render frame results.
     */
    const auto &debug_info = emulator.get_debug_info();
    app.draw_frame(debug_info);
    app.wait_until_frame_over();

    return control_state.app_running;
}

void GameboiPlusPlus::quit()
{
    LogInfo(ANSI_CYAN "Shutting Down...");
    app.quit();
}

} // namespace Gbpp