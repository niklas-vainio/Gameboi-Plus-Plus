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

/**
 * Parsing format for the test dumps, matching the format of the files created
 * by scripts/dump_cpu_tests.py
 */
namespace TestDump
{
/**
 * Struct representing a memr
 */
struct MemoryOp
{
    uint16_t address;
    uint16_t data;
};

/**
 * Struct representing a single configuration of the CPU. Matches the dump
 * created by scripts/dump_cpu_tests.py.
 */
struct CpuState
{
    uint8_t A, B, C, D, E, F, H, L;
    uint16_t pc, sp;
    uint16_t ime, ie;

    uint32_t num_memory_ops;
    MemoryOp memory_ops[5];
};
} // namespace TestDump

class CpuTest
{
public:
    /**
     * Main test entry point, which runs tests for all opcodes.
     *
     * @return True on success, false otherwise.
     */
    bool run();

private:
    /**
     * Run all tests for a single opcode.
     *
     * @param opcode    Opcode to run tests for.
     * @param cp_prefix Whether to use a CB-prefixed opcode.
     * @return True on success, false otherwise.
     */
    bool run_opcode_tests(const uint8_t opcode, bool cb_prefix);

    /**
     * Run all tests for a single CB-prefixed opcode.
     *
     * @param opcode    Opcode to run tests for.
     * @return True on success, false otherwise.
     */
    bool run_opcode_tests_cb_prefixed(const uint8_t opcode);

    /**
     * Run a single test.
     *
     * @param[in] opcode            Opcode we are running.
     * @param[in] cp_prefix         Use a CB-prefixed opcode.
     * @param[in] initial_state     Initial CPU state.
     * @param[in] final_state       Final CPU state.
     * @return True on success, false otherwise.
     */
    bool run_single_test(const uint8_t opcode,
                         bool cp_prefix,
                         const TestDump::CpuState &initial_state,
                         const TestDump::CpuState &final_state);

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
