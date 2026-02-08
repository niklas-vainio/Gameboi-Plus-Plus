/**
 * Generic class representing a blob of memory with a fixed base address and
 * size.
 *
 * @author Niklas Vainio
 * @date 2026-02-07
 */

#pragma once

#include "common/logging.hpp"
#include <array>
#include <cstdint>

namespace Gbpp::Backend
{

/**
 * @tparam Start   The lowest address in the reion (inclusive).
 * @tparam End     The highest address in the region (inclusive).
 */
template <std::uint16_t Start, std::uint16_t End>
class RamRegion
{
public:
    /**
     * Overall size (in bytes) of the region.
     */
    static_assert(End >= Start + 1, "Ram regions must have non-zero size");
    static constexpr std::size_t Size = (End + 1) - Start;

    RamRegion() = default;

    /**
     * Disallow copy and move.
     */
    RamRegion(const RamRegion &) = delete;
    RamRegion &operator=(const RamRegion &) = delete;
    RamRegion(RamRegion &&) = delete;
    RamRegion &operator=(RamRegion &&) = delete;

    /**
     * Read a single byte the specified absolute address.
     *
     * @paRamRegion[in] address   Address to read from
     * @return The value at that address.
     */
    uint8_t read(const uint16_t address)
    {
        LogDebug("Reading RAM address %04X", address);
        return data.at(address - Start);
    }

    /**
     * Wrote a single byte to the specified absolute address.
     *
     * @paRamRegion[in] address   Address to write to
     * @paRamRegion[in] value     The value to write
     */
    void write(const uint16_t address, const uint8_t value)
    {
        LogDebug("Writing %02X to RAM address %04X", value, address);
        data.at(address - Start) = value;
    }

private:
    /**
     * Underlying array backing the data.
     */
    std::array<uint8_t, Size> data{};
};

} // namespace Gbpp::Backend