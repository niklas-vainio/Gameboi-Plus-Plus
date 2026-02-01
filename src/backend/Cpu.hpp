/**
 * Main class for emulating the Game Boy's SM83 CPU/
 *
 * References:
 *      https://rgbds.gbdev.io/docs/v1.0.1/rgbasm.5
 *      https://gbdev.io/gb-opcodes/optables/
 *
 * @author Niklas Vainio
 * @date   2026-02-01
 */

#pragma once

#include "Bus.hpp"
#include "common/DebugInfo.hpp"

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

    /**
     * Number of cycles elapsed.
     */
    uint64_t num_cycles_elapsed{};

    /**
     * Number of instructions executed.
     */
    uint64_t num_instructions_executed{};
};

} // namespace Gbpp::Backend