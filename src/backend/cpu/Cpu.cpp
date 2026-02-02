/**
 * Main class for emulating the Game Boy's SM83 CPU.
 *
 * References:
 *      https://rgbds.gbdev.io/docs/v1.0.1/rgbasm.5
 *      https://gbdev.io/gb-opcodes/optables/
 *
 * @author Niklas Vainio
 * @date   2026-02-01
 */

#include "Cpu.hpp"

namespace Gbpp::Backend
{

void Cpu::emulate_instruction()
{
    /*
     * Fetch opcode.
     */

    /*
     * Decode the instruction, handling CB-prefixed instructions separately.
     */

    /*
     * Execute the instruction.
     */
    num_instructions_executed++;
    num_cycles_elapsed += 4;
}

CpuDebugInfo Cpu::get_debug_info()
{
    return {.num_instructions_executed = num_instructions_executed,
            .num_cycles_elapsed = num_cycles_elapsed,

            .A = A,
            .B = B,
            .C = C,
            .D = D,
            .E = E,
            .F = F,
            .H = H,
            .L = L,
            .pc = pc,
            .sp = sp,

            .current_instruction_asm = current_instruction_asm};
}

} // namespace Gbpp::Backend