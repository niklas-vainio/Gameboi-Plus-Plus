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

#pragma once

#include "backend/Bus.hpp"
#include "common/DebugInfo.hpp"
#include <array>
#include <string>

namespace Gbpp::Backend
{

class Cpu
{
public:
    /**
     * Constructor.
     */
    Cpu(Bus &bus_) : bus(bus_) {};

    /**
     * Run a single emulated instruction.
     */
    void emulate_instruction();

    /**
     * Disallow copy/move.
     */
    Cpu(const Cpu &) = delete;
    Cpu(Cpu &&) = delete;
    Cpu &operator=(const Cpu &) = delete;
    Cpu &operator=(Cpu &&) = delete;

    /**
     * @return A CpuDebugInfo structure reflecting the current state.
     */
    CpuDebugInfo get_debug_info();

private:
    /**
     * Reference to the bus.
     */
    Bus &bus;

    /**
     * Helper functions for reading and writing.
     */
    uint8_t read(const uint16_t address)
    {
        return bus.read(address);
    };
    void write(const uint16_t address, const uint8_t value)
    {
        bus.write(address, value);
    };

    /**
     * Registers
     */
    uint8_t A{}, B{}, C{}, D{}, E{}, F{}, H{}, L{};
    uint16_t pc{};
    uint16_t sp{};

    /**
     * Number of cycles elapsed.
     */
    uint64_t num_cycles_elapsed{};

    /**
     * Number of instructions executed.
     */
    uint64_t num_instructions_executed{};

    /**
     * Assembly string representation of the current instruction.
     */
    std::string current_instruction_asm = "???";

    /**
     * Prototypes of all opcode functions - included from a separate file.
     *
     * Implementations are defined in instructions.cpp
     */
#include "instruction_prototypes.hpp"

    /**
     * Struct defining data about an instruction.
     */
    using InstructionFunc = void (Cpu::*)();
    struct Instruction
    {
        InstructionFunc func;
        uint8_t opcode;
        uint8_t bytes;
        uint8_t cycles;
    };

    /**
     * Mapping from opcodes to instructions - included from a separate file.
     *
     * The following members are defined:
     *      instruction_map
     *      instruction_map_cb_prefixed
     */
#include "instruction_map.hpp"
#include "instruction_map_cb_prefixed.hpp"
};

} // namespace Gbpp::Backend