/**
 * Simple test for now.
 *
 * @author Niklas Vainio
 * @date   2026-01-25
 */

#include "GameboiPlusPlus.hpp"
#include "common/logging.hpp"
#include "common/unused.hpp"

int main(int argc, const char **argv)
{
    /*
     * Parse args.
     */
    UNUSED(argc);
    UNUSED(argv);

    /*
     * Instantiate app and run forever.
     */
    Gbpp::GameboiPlusPlus({.debug = false}).go();

    LogInfo(ANSI_GREEN "All done, thanks for playing! :)");
    return EXIT_SUCCESS;
}