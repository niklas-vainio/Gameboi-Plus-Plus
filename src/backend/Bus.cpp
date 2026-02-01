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

uint8_t Bus::read(const uint16_t address)
{
    LogDebug("Read from address %02x", address);

    return 0x00;
}

void Bus::write(const uint16_t address, const uint8_t value)
{
    LogDebug("Write %02x to address %04x", value, address);
}

} // namespace Gbpp::Backend