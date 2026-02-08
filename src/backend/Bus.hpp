/**
 * Class representing the bus, which dispatches reads and writes from the CPU to
 * peripherals.
 *
 * @author Niklas Vainio
 * @date   2026-02-01
 */

#pragma once

#include "RamRegion.hpp"
#include "RomFile.hpp"
#include <cstdint>
#include <string>

namespace Gbpp::Backend
{

class Bus
{
public:
    /**
     * Load a ROM file.
     *
     * @param[in] rom_path  Path of the file to load.
     * @return True on success, false otherwise.
     */
    bool load_rom(const std::string &rom_path);

    /**
     * Read a single byte the specified address.
     *
     * @param[in] address   Address to read from
     * @return The value at that address.
     */
    uint8_t read(const uint16_t address);

    /**
     * Wrote a single byte to the specified address.
     *
     * @param[in] address   Address to write to
     * @param[in] value     The value to write
     */
    void write(const uint16_t address, const uint8_t value);

private:
    /**
     * Internal ROM file. Mapped from 0x0000-0x7FFF.
     */
    RomFile rom{};

    /**
     * TODO: Vram. Mapped from 0x8000-0x9FFF.
     */

    /**
     * TODO: External ram (8KiB). Mapped from 0xA000-0xBFFF.
     */

    /**
     * Work ram (8KiB). Mapped from 0xC000-0xDFFF, and mirrored to
     * 0xE000-0xFDFF.
     */
    RamRegion<0xC000, 0xDFFF> work_ram{};

    /**
     * High RAM (127B). Mapped from 0xFF80-0xFFFE.
     */
    RamRegion<0xFF80, 0xFFFE> high_ram{};

    uint8_t serial_data{};
};

} // namespace Gbpp::Backend