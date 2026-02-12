"""
Helper script to dump CPU tests into a compact struct that cam be loaded easily
from C++
"""
import json
import struct

NUM_MEMORY_OPS = 5

def pack_setup(setup: dict) -> bytes:
    regs = struct.Struct("BBBBBBBBHH") # A, B, C, D, E, F, H, L, pc, sp
    interrupts = struct.Struct("HH") # ime, ie, if, halted
    num_memory_ops = struct.Struct("I") # number of memory operations (for padding)
    memory_op = struct.Struct("HH") # address, value (as a 16 bit value for padding)

    output = bytearray()
    output += regs.pack(
        setup["a"],
        setup["b"],
        setup["c"],
        setup["d"],
        setup["e"],
        setup["f"],
        setup["h"],
        setup["l"],
        setup["pc"],
        setup["sp"],
    )

    output += interrupts.pack(
        setup["ime"],
        setup.get("ie", 0),
    )

    assert len(setup["ram"]) <= NUM_MEMORY_OPS, "Too many memory operations for struct packing"

    output += num_memory_ops.pack(len(setup["ram"]))

    for i in range(NUM_MEMORY_OPS):
        if i < len(setup["ram"]):
            op = setup["ram"][i]
            output += memory_op.pack(op[0], op[1])
        else:
            output += memory_op.pack(0, 0)
    
    return bytes(output)


def dump_test(test: dict) -> bytes:
    return pack_setup(test["initial"]) + pack_setup(test["final"])

def dump_tests_for_opcode(opcode: bytes, output_file: str, cb_prefix = True):
    print(f"Writing tests for {'CB' if cb_prefix else ''} {opcode:02X}...")
    with open(f"local/cpu_tests/v1/{'cb ' if cb_prefix else ''}{opcode:02x}.json", "r") as f:
        test_data = json.load(f)

    # Write all test dumps to binary file
    with open(output_file, "wb") as f:
        for test in test_data:
            f.write(dump_test(test))


if __name__ == "__main__":

    ILLEGAL_OPCODES = [0xd3, 0xdb, 0xdd, 0xe3, 0xe4, 0xeb, 0xec, 0xed, 0xf4, 0xfc, 0xfd]

    # Write tests for all opcodes
    for opcode in range(0x100):
        if opcode in ILLEGAL_OPCODES or opcode == 0xcb:
            continue
        dump_tests_for_opcode(opcode, f"resources/cpu_tests/tests_{opcode:02x}.bin", cb_prefix=False)
    for opcode in range(0x100):
        dump_tests_for_opcode(opcode, f"resources/cpu_tests/tests_cb_{opcode:02x}.bin", cb_prefix=True)

    print("\n\n\nAll done!\n")