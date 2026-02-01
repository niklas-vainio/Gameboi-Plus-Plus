/**
 * This file defines the information about the emulator which is passed to the
 * frontend to render the debug panel.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include <cstdint>

namespace Gbpp
{

struct EmulatorDebugInfo
{
    uint64_t num_instructions_executed{};
};

} // namespace Gbpp