#include "CPU.h"
#include <cstdint>

/*
 * The 6502 contains 13 addressing modes in total, including 6 indexed (using
 * the X and Y registers) and 7 unindexed.
 *
 * The purpose of addressing modes is to determine how to get, and return, the
 * operand of an operation. So for example in the case of Accumulator, the
 * operand is the Accumulator. In the case of Immediate addressing, the operand
 * is the 8 bit value that the PC is pointing to.
 *
 * */

/*---------------------------------
 * INDEXED ADDRESSING MODES
---------------------------------*/

uint8_t CPU::ZeroPageIndexedX() { return PC; }

uint8_t CPU::ZeroPageIndexedY() { return PC; }

uint8_t CPU::AbsoluteIndexedX() { return PC; }

uint8_t CPU::AbsoluteIndexedY() { return PC; }

uint8_t CPU::IndexedIndirectX() { return PC; }

uint8_t CPU::IndirectIndexedY() { return PC; }

/*---------------------------------
 * OTHER ADDRESSING MODES
---------------------------------*/

uint8_t CPU::Implicit() { return PC; }

uint8_t CPU::Accumulator() { return PC; }

uint8_t CPU::Immediate() { return PC; }

uint8_t CPU::ZeroPage() { return PC; }

uint8_t CPU::Absolute() { return PC; }

uint8_t CPU::Relative() { return PC; }

uint8_t CPU::Indirect() { return PC; }
