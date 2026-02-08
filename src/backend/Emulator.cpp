
/**
 * Main entry point for the backend, which handles actual emulation.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#include "Emulator.hpp"
#include "Bus.hpp"
#include "common/GameBoyConstants.hpp"
#include "common/abort.hpp"
#include "common/logging.hpp"
#include "common/resource.hpp"

namespace Gbpp::Backend
{

bool Emulator::init(const std::string &rom_path)
{
    /*
     * Load the provided ROM file.
     */
    const auto rom_path_full = Resource::get_resource_path(rom_path);
    AbortIfNot(bus.load_rom(rom_path_full), false);

    LogInfo(ANSI_CYAN "Emulator backend initialized successfully!");
    return true;
}

void Emulator::emulate_frame(const ControlState &control_state)
{
    if (control_state.run_many_instructions)
    {
        for (auto i = 0; i < GameBoyConstants::clock_cycles_per_frame / 4; i++)
        {
            emulate_instruction();
        }
    }
    else if (control_state.run_single_instruction)
    {
        emulate_instruction();
    }

    update_debug_info();
}

void Emulator::emulate_instruction()
{
    cpu.emulate_instruction();
}

void Emulator::update_debug_info()
{
    debug_info.cpu = cpu.get_debug_info();
}

} // namespace Gbpp::Backend