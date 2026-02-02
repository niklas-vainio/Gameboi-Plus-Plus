/**
 * This file defines the information about the emulator which is passed to the
 * frontend to render the debug panel.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include <cstdint>
#include <string>

namespace Gbpp
{

/**
 * Information about the CPU.
 */
struct CpuDebugInfo
{
    uint64_t num_instructions_executed{};
    uint64_t num_cycles_elapsed{};

    uint8_t A{}, B{}, C{}, D{}, E{}, F{}, H{}, L{};
    uint16_t pc{};
    uint16_t sp{};

    std::string current_instruction_asm{};
};

/**
 * Main struct passed to the frontend.
 */
struct EmulatorDebugInfo
{
    CpuDebugInfo cpu{};
};

} // namespace Gbpp