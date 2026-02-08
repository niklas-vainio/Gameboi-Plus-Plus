/**
 * Class representing the bus, which dispatches reads and writes from the CPU to
 * peripherals.
 *
 * @author Niklas Vainio
 * @date   2026-02-01
 */

#include "Bus.hpp"
#include "common/logging.hpp"

namespace Gbpp::Backend
{

bool Bus::load_rom(const std::string &rom_path)
{
    const auto result = rom.load(rom_path);
    LogDebug("Loaded %zu bytes", rom.size());
    return result;
}

uint8_t Bus::read(const uint16_t address)
{
    if (0x0000 <= address && address <= 0x7FFF)
    {
        /**
         * 0x0000-0x7FFF: Cartridge
         */
        return rom[address];
    }
    if (0x8000 <= address && address <= 0x9FFF)
    {
        /**
         * 0x8000-0x9FFF: VRAM
         */
        LogWarning("Unimplemented VRAM read at address %04X", address);
        return 0xFF;
    }
    if (0xA000 <= address && address <= 0xBFFF)
    {
        /**
         * 0xA000-0xBFFF: External ram
         */
        LogWarning("Unimplemented ExRam read at address %04X", address);
        return 0xFF;
    }
    if (0xC000 <= address && address <= 0xDFFF)
    {
        /**
         * 0xC000-0xDFFF: Work RAM
         */
        return work_ram.read(address);
    }
    if (0xE000 <= address && address <= 0xFDFF)
    {
        /**
         * 0xE000-0xFDFF: Work RAM mirror
         */
        return work_ram.read(address - 0x2000);
    }
    if (0xFE00 <= address && address <= 0xFE9F)
    {
        /**
         * 0xFE00-0xFE9F: OAM
         */
        LogWarning("Unimplemented OAM read at address %04X", address);
        return 0xFF;
    }
    if (0xFEA0 <= address && address <= 0xFEFF)
    {
        /**
         * 0xFEA0-0xFEFF: Illegal area
         */
        LogError("Read from illegal area at address %04X", address);
        return 0x00;
    }
    if ((0xFF00 <= address && address <= 0xFF7F) || address == 0xFFFF)
    {
        /**
         * 0xFF00-0xFF7F and 0xFFFF: IO Registers (including interrupt enable)
         */
        LogWarning("Unimplemented IO reg read at address %04X", address);
        return 0xFF;
    }
    if (0xFF80 <= address && address <= 0xFFFE)
    {
        /**
         * 0xFF80-0xFFFE: High RAM
         */
        return high_ram.read(address);
    }

    LogError("Uncaught read from address %04X", address);
    return 0xFF;
}

void Bus::write(const uint16_t address, const uint8_t value)
{
    if (0x0000 <= address && address <= 0x7FFF)
    {
        /**
         * 0x0000-0x7FFF: Cartridge
         */
        LogError("Attempt to write %02x to ROM region at address %04X",
                 value,
                 address);
        return;
    }
    if (0x8000 <= address && address <= 0x9FFF)
    {
        /**
         * 0x8000-0x9FFF: VRAM
         */
        LogWarning("Unimplemented VRAM write at address %04X", address);
        return;
    }
    if (0xA000 <= address && address <= 0xBFFF)
    {
        /**
         * 0xA000-0xBFFF: External ram
         */
        LogWarning("Unimplemented ExRam write at address %04X", address);
        return;
    }
    if (0xC000 <= address && address <= 0xDFFF)
    {
        /**
         * 0xC000-0xDFFF: Work RAM
         */
        work_ram.write(address, value);
        return;
    }
    if (0xE000 <= address && address <= 0xFDFF)
    {
        /**
         * 0xE000-0xFDFF: Work RAM mirror
         */
        work_ram.write(address - 0x2000, value);
        return;
    }
    if (0xFE00 <= address && address <= 0xFEFF)
    {
        /**
         * 0xFE00-0xFE9F: OAM
         */
        LogWarning("Unimplemented OAM write at address %04X", address);
        return;
    }
    if (0xFEA0 <= address && address <= 0xFEFF)
    {
        /**
         * 0xFEA0-0xFEFF: Illegal area
         */
        LogError("Write to illegal area at address %04X", address);
        return;
    }
    if ((0xFF00 <= address && address <= 0xFF7F) || address == 0xFFFF)
    {
        /**
         * 0xFF00-0xFF7F and 0xFFFF: IO Registers (including interrupt enable)
         */
        LogInfo("IO reg write to %04X", address);

        /**
         * FIXME: Temporary - serial data and trigger.
         */
        if (address == 0xFF01)
        {
            serial_data = value;
            return;
        }
        if (address == 0xFF02)
        {
            std::printf("%c", static_cast<char>(serial_data));
            return;
        }

        LogWarning("Unimplemented IO reg read at address %04X", address);
        return;
    }
    if (0xFF80 <= address && address <= 0xFFFE)
    {
        /**
         * 0xFF80-0xFFFE: High RAM
         */
        high_ram.write(address, value);
        return;
    }

    LogError("Uncaught write %02X to address %04X", value, address);
}

} // namespace Gbpp::Backend