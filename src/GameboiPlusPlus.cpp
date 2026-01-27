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
    return app.run_frame();
}

void GameboiPlusPlus::quit()
{
    LogDebug("Shutting Down...");
    app.quit();
}

} // namespace Gbpp