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
    CpuDebugInfo get_debug_info() const;

private:
    /**
     * Reference to the bus.
     */
    Bus &bus;

    /**
     * Helper functions for reading and writing. 16-bit values are read/written
     * in little-endian order.
     */
    uint8_t read_8(const uint16_t address)
    {
        return bus.read(address);
    }
    void write_8(const uint16_t address, const uint8_t value)
    {
        bus.write(address, value);
    }
    uint16_t read_16(const uint16_t address)
    {
        return read_8(address) | (read_8(address + 1) << 8);
    }
    void write_16(const uint16_t address, const uint16_t value)
    {
        write_8(address, value & 0x00ff);
        write_8(address + 1, value >> 8);
    }

    /**
     * Helper functions for fetching opcodes/operands (reading + incrementing
     * PC).
     */
    uint8_t fetch_8()
    {
        return read_8(pc++);
    }
    uint16_t fetch_16()
    {
        const uint16_t value = read_16(pc);
        pc += 2;
        return value;
    }

    /**
     * Helper functions for pushing/popping 16-bit values to/from the stack.
     *
     * The stack is full-descending, meaning it grows down and SP points to the
     * most recently pushed element. Values are stored in memory in
     * little-endian order.
     */
    uint16_t pop_16()
    {
        const uint16_t value = read_16(sp);
        sp += 2;
        return value;
    }
    void push_16(uint16_t value)
    {
        sp += 2;
        write_16(sp, value);
    }

    /**
     * Registers.
     *
     * FIXME: Don't start pc at 0x0100 once bios is implemented.
     */
    uint8_t A{}, B{}, C{}, D{}, E{}, F{}, H{}, L{};
    uint16_t pc{0x0100};
    uint16_t sp{};

    /**
     * Getters and setters for 16-bit register pairs. Setter for AF makes sure
     * lower 4 bits of F are always zero.
     */
    // clang-format off
    uint16_t get_AF() const { return A << 8 | F; }
    uint16_t get_BC() const { return B << 8 | C; }
    uint16_t get_DE() const { return D << 8 | E; }
    uint16_t get_HL() const { return H << 8 | L; }

    void set_AF(uint16_t AF) { A = AF >> 8; F = AF & 0xf0; }
    void set_BC(uint16_t BC) { B = BC >> 8; C = BC & 0xff; }
    void set_DE(uint16_t DE) { D = DE >> 8; E = DE & 0xff; }
    void set_HL(uint16_t HL) { H = HL >> 8; L = HL & 0xff; }
    // clang-format on

    /**
     * Getters and setters for CPU flags.
     */
    // clang-format off
    bool get_Z() const { return F & (1 << 7); }
    bool get_N() const { return F & (1 << 6); }
    bool get_H() const { return F & (1 << 5); }
    bool get_C() const { return F & (1 << 4); }

    void set_Z(bool Z) { F = (F & ~(1 << 7)) | (Z << 7); }
    void set_N(bool N) { F = (F & ~(1 << 6)) | (N << 6); }
    void set_H(bool H) { F = (F & ~(1 << 5)) | (H << 5); }
    void set_C(bool C) { F = (F & ~(1 << 4)) | (C << 4); }
    // clang-format on

    /**
     * Number of cycles elapsed.
     */
    uint64_t num_cycles_elapsed{};

    /**
     * Number of instructions executed.
     */
    uint64_t num_instructions_executed{};

    /**
     * Current instruction opcode.
     */
    uint8_t opcode{};

    /**
     * Assembly string representation of the current instruction.
     */
    std::string current_instruction_asm = "???";

    /**
     * Store whether interrupts are currently enabled;
     */
    bool interrupts_enbled{};

    /**
     * Store whether the CPU is currently halted or stopped (via the HALT/STOP
     * instructions).
     */
    bool halted{};
    bool stopped{};

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