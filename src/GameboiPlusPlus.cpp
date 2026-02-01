/**
 * Main class holding all app state.
 *
 * @author Niklas Vainio
 * @date   2026-01-25
 */

#include "GameboiPlusPlus.hpp"
#include "common/logging.hpp"

namespace Gbpp
{

void GameboiPlusPlus::go()
{
    /*
     * Initialize.
     */
    if (!init())
    {
        LogError("Failed initialization, quitting!");
        quit();
        return;
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
}

bool GameboiPlusPlus::init()
{
    LogDebug("Initializing...");
    return app.init();
}

bool GameboiPlusPlus::run_frame()
{
    app.start_frame();

    /*
     * Collect user inputs
     */
    const auto control_state = app.handle_inputs();

    /*
     * Dispatch the emulator for this frame.
     */

    /*
     * Render frame results.
     */
    app.render_frame();
    app.wait_until_frame_over();

    return control_state.app_running;
}

void GameboiPlusPlus::quit()
{
    LogDebug("Shutting Down...");
    app.quit();
}

} // namespace Gbpp