#include "CPU.h"

void CPU::NMI() { int test = 1 + 1; }

CPU::CPU() { NMI(); }

// Returns whether a flag in the status register (P) is set or clear
bool CPU::GET_FLAG(int flag) { return (P & (1 << flag)); }

// Sets flag in the status register, ORs the status register with 1 left shifted
// by the bit of the flag to be set. For example, for setting interrupt disable
// (bit 2, or "the 3rd bit"), 1 << 2 is 0000 0100, 1111 1010 | 0000 0100 = 1111
// 1110
void CPU::SET_FLAG(int flag) { (P |= (1 << flag)); }

// Clears flag in the status register, ANDs the status register with the inverse
// of 1 left shifted by the bit of the flag to be set. For example, for clearing
// interrupt disable (bit 2, or "the 3rd bit"), 1 << 2 is 0000 0100, that
// inverted is 1111 1011, and 1111 1110 & 1111 1011 = 1111 1010
void CPU::CLEAR_FLAG(int flag) { (P &= ~(1 << flag)); }
