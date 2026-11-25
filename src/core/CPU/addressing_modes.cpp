#include "CPU.h"
#include <cstdint>

/*
 * The 6502 contains 13 addressing modes in total, including 6 indexed (using
 * the X and Y registers) and 7 unindexed.
 *
 * The purpose of addressing modes is to determine how to get, and return, the
 * operand of an operation. So for example in the case of Accumulator, the
 * operand is the Accumulator. In the case of Immediate addressing, the operand
 * is the 16 bit value that the PC is pointing to.
 *
 * */

/*---------------------------------
 * INDEXED ADDRESSING MODES
---------------------------------*/

uint16_t CPU::ZERO_PAGE_INDEXED_X() { return PC; }

uint16_t CPU::ZERO_PAGE_INDEXED_Y() { return PC; }

uint16_t CPU::ABSOLUTE_INDEXED_X() { return PC; }

uint16_t CPU::ABSOLUTE_INDEXED_Y() { return PC; }

uint16_t CPU::INDEXED_INDIRECT_X() { return PC; }

uint16_t CPU::INDIRECT_INDEXED_Y() { return PC; }

/*---------------------------------
 * OTHER ADDRESSING MODES
---------------------------------*/

uint16_t CPU::IMPLICIT() { return PC; }

uint16_t CPU::ACCUMULATOR() { return PC; }

uint16_t CPU::IMMEDIATE() { return PC; }

uint16_t CPU::ZERO_PAGE() { return PC; }

uint16_t CPU::ABSOLUTE() { return PC; }

uint16_t CPU::RELATIVE() { return PC; }

uint16_t CPU::INDIRECT() { return PC; }
