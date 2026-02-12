/**
 * Simple test for now.
 *
 * @author Niklas Vainio
 * @date   2026-01-25
 */

#include "GameboiPlusPlus.hpp"
#include "common/logging.hpp"
#include "common/unused.hpp"
#include "tests/CpuTest.hpp"

int main(int argc, const char **argv)
{
#ifdef CPU_TEST
    /*
     * Run CPU tests.
     */
    UNUSED(argc);
    UNUSED(argv);
    return Gbpp::Test::CpuTest{}.run() ? EXIT_SUCCESS : EXIT_FAILURE;
#else

    /*
     * Parse args.
     */
    if (argc < 2)
    {
        std::printf("\nUsage: gameboi++ <path_to_rom.gb>\n");
        return EXIT_FAILURE;
    }

    /*
     * Instantiate app and run forever.
     */
    const auto success = Gbpp::GameboiPlusPlus({.rom_path = {argv[1]}}).go();

    if (success)
    {
        LogInfo();
        LogInfo(ANSI_GREEN "All done, thanks for playing! :)");
        LogInfo();
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
#endif
}