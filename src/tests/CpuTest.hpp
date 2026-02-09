/**
 * Test class for validating CPU opcode behavior. The implementation in
 * CpuTest.cpp is auto-generated.
 *
 * @author Niklas Vainio
 * @date   2026-02-08
 */

#pragma once

#include "backend/cpu/Cpu.hpp"
#include <array>

namespace Gbpp::Test
{

/**
 * Mock bus class containing only 64 kiB of RAM.
 */
class RamOnlyBus
{
public:
    uint8_t read(const uint16_t address)
    {
        return data.at(address);
    }
    void write(const uint16_t address, const uint8_t value)
    {
        data.at(address) = value;
    }

    void reset()
    {
        data.fill(0);
    }

private:
    std::array<uint8_t, 0x10000> data{};
};

class CpuTest
{
public:
    /**
     * Main test entry point.
     *
     * @return True on success, false otherwise.
     */
    bool run();

private:
    /**
     * Instance of the mock bus.
     */
    RamOnlyBus bus{};

    /**
     * Internal CPU.
     */
    Gbpp::Backend::Cpu<decltype(bus)> cpu{bus};
};

} // namespace Gbpp::Test
