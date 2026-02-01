
/**
 * Main entry point for the backend, which handles actual emulation.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#include "Emulator.hpp"
#include "common/logging.hpp"

namespace Gbpp::Backend
{

bool Emulator::init()
{
    LogInfo(ANSI_PURPLE "Emulator backend initialized!");

    return true;
}

void Emulator::emulate_frame(const ControlState &control_state)
{
    if (control_state.run_cpu_instruction)
    {
        emulate_instruction();
    }

    update_debug_info();
}

void Emulator::emulate_instruction()
{
    num_instructions_executed++;
}

void Emulator::update_debug_info()
{
    debug_info.num_instructions_executed = num_instructions_executed;
}

} // namespace Gbpp::Backend