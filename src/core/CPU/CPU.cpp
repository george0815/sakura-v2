#include "CPU.h"

void CPU::NMI() { int test = 1 + 1; }

CPU::CPU() { NMI(); }
