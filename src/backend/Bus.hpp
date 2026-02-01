/**
 * Class representing the bus, which dispatches reads and writes from the CPU to
 * peripherals.
 *
 * @author Niklas Vainio
 * @date   2026-02-01
 */

#pragma once

#include <cstdint>

namespace Gbpp::Backend
{

class Bus
{
public:
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
};

} // namespace Gbpp::Backend