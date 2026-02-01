/**
 * This file defines the user input information passed from the frontend to the
 * backend.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

namespace Gbpp
{

/**
 * Struct defining the current state of all user control inputs.
 *
 * The inputs are logged by the frontend and passed to the backend, where they
 * influence the emulation.
 */
struct ControlState
{
    bool app_running{true};
    bool run_cpu_instruction{};
};

} // namespace Gbpp