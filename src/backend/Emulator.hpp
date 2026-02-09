
/**
 * Main entry point for the backend, which handles actual emulation.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include "Bus.hpp"
#include "common/Control.hpp"
#include "common/DebugInfo.hpp"
#include "cpu/Cpu.hpp"
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
     * @param[in] rom_path      Path of the rom to load
     * @return True on success, false otherwise.
     */
    bool init(const std::string &rom_path);

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
     * Emulate a single Cpu instruction.
     */
    void emulate_instruction();

    /**
     * Update the locally stored debug info to reflect the current state.
     */
    void update_debug_info();

    /**
     * Bus object.
     */
    Bus bus{};

    /**
     * Cpu object, linked to the bus.
     */
    Cpu<decltype(bus)> cpu{bus};

    /**
     * Information about the current state, passed to the frontend for
     * rendering.
     *
     * Stored locally here to keep ownership of this data within the backend.
     */
    EmulatorDebugInfo debug_info{};
};

} // namespace Gbpp::Backend