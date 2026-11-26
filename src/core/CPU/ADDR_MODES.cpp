#include "CPU_6502.h"
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

uint16_t CPU_6502::ZERO_PAGE_INDEXED_X() { return PC; }

uint16_t CPU_6502::ZERO_PAGE_INDEXED_Y() { return PC; }

uint16_t CPU_6502::ABSOLUTE_INDEXED_X() { return PC; }

uint16_t CPU_6502::ABSOLUTE_INDEXED_Y() { return PC; }

uint16_t CPU_6502::INDEXED_INDIRECT_X() { return PC; }

uint16_t CPU_6502::INDIRECT_INDEXED_Y() { return PC; }

/*---------------------------------
 * OTHER ADDRESSING MODES
---------------------------------*/

uint16_t CPU_6502::IMPLICIT() { return PC; }

uint16_t CPU_6502::ACCUMULATOR() { return PC; }

uint16_t CPU_6502::IMMEDIATE() { return PC; }

uint16_t CPU_6502::ZERO_PAGE() { return PC; }

uint16_t CPU_6502::ABSOLUTE() { return PC; }

uint16_t CPU_6502::RELATIVE() { return PC; }

uint16_t CPU_6502::INDIRECT() { return PC; }
