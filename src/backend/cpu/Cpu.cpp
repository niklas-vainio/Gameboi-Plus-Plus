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
    /**
     * Do nothing if HALT/STOP has been called.
     */
    if (halted || stopped)
    {
        return;
    }

    /*
     * Fetch opcode.
     */
    opcode = fetch_8();

    /*
     * Decode the instruction. Read an extra opcode byte for CB-prefixed
     * instructions, but keep the opcode field as CB for debug info.
     */
    const auto &instruction = (opcode == 0xCB)
                                  ? instruction_map_cb_prefixed[read_8(pc++)]
                                  : instruction_map[opcode];

    /*
     * Execute the instruction and increase cycle counts.
     */
    (this->*instruction.func)();
    num_instructions_executed++;
    num_cycles_elapsed += instruction.cycles;
}

CpuDebugInfo Cpu::get_debug_info() const
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

            .opcode = opcode,
            .current_instruction_asm = current_instruction_asm};
}

} // namespace Gbpp::Backend