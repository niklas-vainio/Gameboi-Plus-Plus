# Helper script to auto-generate CPU test cases

import json


TEST_SETUP_TEMPLATE = """\
cpu.A = 0x{a:02x};
cpu.B = 0x{b:02x};
cpu.C = 0x{c:02x};
cpu.D = 0x{d:02x};
cpu.E = 0x{e:02x};
cpu.F = 0x{f:02x};
cpu.H = 0x{h:02x};
cpu.L = 0x{l:02x};
cpu.pc = 0x{pc:04x};
cpu.sp = 0x{sp:04x};
"""

TEST_SETUP_RAM_TEMPLATE = """\
bus.write(0x{address:04x}, 0x{value:02x});
"""

TEST_ASSERT_TEMPLATE = """\
AssertEq(cpu.A, 0x{a:02x});
AssertEq(cpu.B, 0x{b:02x});
AssertEq(cpu.C, 0x{c:02x});
AssertEq(cpu.D, 0x{d:02x});
AssertEq(cpu.E, 0x{e:02x});
AssertEq(cpu.F, 0x{f:02x});
AssertEq(cpu.H, 0x{h:02x});
AssertEq(cpu.L, 0x{l:02x});
AssertEq(cpu.pc, 0x{pc:04x});
AssertEq(cpu.sp, 0x{sp:04x});
"""

TEST_ASSERT_RAM_TEMPLATE = """\
AssertEq(bus.read(0x{address:04x}), 0x{value:02x});
"""

def format_test(test: dict):
    test_setup = TEST_SETUP_TEMPLATE.format(**test["initial"])
    test_ram_setup = "\n".join(
        TEST_SETUP_RAM_TEMPLATE.format(address=ram[0], value=ram[1]) for ram in test["initial"]["ram"]
    )

    instruction = "cpu.emulate_instruction();"
    
    test_assert = TEST_ASSERT_TEMPLATE.format(**test["final"])
    test_ram_assert = "\n".join(
        TEST_ASSERT_RAM_TEMPLATE.format(address=ram[0], value=ram[1]) for ram in test["final"]["ram"]
    )

    return f"{test_setup}{test_ram_setup}\n{instruction}\n\n{test_assert}{test_ram_assert}"


def create_tests_for_opcode(opcode):
    with open(f"local/cpu_tests/v1/{opcode:02x}.json", "r") as f:
        test_data = json.load(f)

    print(format_test(test_data[0]))


create_tests_for_opcode(0x00)