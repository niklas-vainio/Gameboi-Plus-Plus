/**
 * Class representing the bus, which dispatches reads and writes from the CPU to
 * peripherals.
 *
 * @author Niklas Vainio
 * @date   2026-02-01
 */

#include "Cpu.hpp"

namespace Gbpp::Backend
{

void Cpu::emulate_instruction()
{
    num_instructions_executed++;
    num_cycles_elapsed += 4;
}

CpuDebugInfo Cpu::get_debug_info()
{
    return {.num_instructions_executed = num_instructions_executed,
            .num_cycles_elapsed = num_cycles_elapsed};
}

} // namespace Gbpp::Backend