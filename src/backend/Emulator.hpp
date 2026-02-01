
/**
 * Main entry point for the backend, which handles actual emulation.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include "common/Control.hpp"
#include "common/EmulatorDebugInfo.hpp"
#include <string>

namespace Gbpp::Backend
{

class Emulator
{
public:
    /**
     * TODO:
     *
     * const int *get_framebuffer() const;
     * const int *pop_audio_samples();
     * auto get_debug_info() const;
     * void set_controller_inputs();
     * void load_cartridge(const std::string &rom_file);
     *
     *
     */

    /**
     * Initialize the emulator.
     *
     * @return True on success, false otherwise.
     */
    bool init();

    /**
     * Emulate a single frame.
     *
     * @param[in] control_state     Current user inputs.
     */
    void emulate_frame(const ControlState &control_state);

    /**
     * @return The current debug info.
     */
    const EmulatorDebugInfo &get_debug_info() const
    {
        return debug_info;
    }

private:
    /**
     * Emulate a single CPU instruction.
     */
    void emulate_instruction();

    /**
     * Update the locally stored debug info to reflect the current state.
     */
    void update_debug_info();

    /**
     * Information about the current state, passed to the frontend for
     * rendering.
     */
    EmulatorDebugInfo debug_info{};

    /**
     * Total number of instructions executed.
     */
    uint64_t num_instructions_executed{};
};

} // namespace Gbpp::Backend