/**
 * Main class holding all app state.
 *
 * @author Niklas Vainio
 * @date   2026-01-25
 */

#include "backend/Emulator.hpp"
#include "common/unused.hpp"
#include "frontend/App.hpp"
#include <string>

namespace Gbpp
{

class GameboiPlusPlus
{
public:
    /**
     * Struct representing command line arguments.
     */
    struct Args
    {
        /**
         * The filename of the ROM to load.
         */
        std::string rom_path;
    };

    GameboiPlusPlus(const Args &&args)
        : rom_path(args.rom_path), app(), emulator()
    {
        UNUSED(args);
    };

    /**
     * Main method to run until the app exits.
     *
     * @return True on successful exit, false otherwise.
     */
    bool go();

private:
    /**
     * Initialize the emulator.
     *
     * @return True on success, false otherwise.
     */
    bool init();

    /**
     * Process and render a single frame.
     *
     * @return True if the app should continue running, false otherwise.
     */
    bool run_frame();

    /**
     * Run when the app exits.
     */
    void quit();

    /**
     * File path of rom to load.
     */
    std::string rom_path;

    /**
     * Main class for the frontend, which manages all graphics, audio and input.
     */
    Frontend::App app;

    /**
     * Main class for the backend, which handles all actual emulation logic.
     */
    Backend::Emulator emulator;
};

} // namespace Gbpp