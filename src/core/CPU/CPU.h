

#include <cstdint>

// Main class representing the CPU. For this emulator I went with a lookup table
// appraach with the opcodes as oppossed to the mega-switch statement appraach
// that is sometimes seen.
//
// Helper functions for gettings and settings flags, as well as branching are
// also included. Now, you may see that I never use private values. This is by
// design. This is not production code and creating getters and setters is extra
// work. An emulator is already pretty complicated to write so I wanted to make
// things as simple as possible.

class CPU {

public:
  /*-------------------------
   * REGISTERS
   ------------------------*/

  uint8_t A = 0; // Accumulator
  uint8_t X = 0; // Y Register
  uint8_t Y = 0; // X Register
  uint8_t S =
      0; // Stack Pointer, indexes into the stack at $0100 - $01FF (256 bytes)
         // The NES uses an descending stack, which means that a value of FF for
         // the stack pointer mean that its empty, and that pushing something to
         // the stack will decrease the SP to FE.
  uint8_t P = 0;   // Status Register
  uint16_t PC = 0; // 2 byte program counter

  /*-------------------------
   * INTERRUPT VECTORS
   ------------------------*/

  // The vectors are basically the location that the CPU jumps to when a given
  // interrupt occurs. For example in the case of a IRQ it will generally read a
  // new PC from FFFE - FFFF, the execute from there.

  uint16_t resetVector = 0xFFFC;
  uint16_t irqVector = 0xFFFE;
  uint16_t nmiVector = 0xFFFA;

  /*-------------------------
   * HELPER FUNCTIONS
   ------------------------*/

  void Branch();

  bool GetFlag();

  void SetFlag();

  /*-------------------------
   * ADDRESSING MODES
   ------------------------*/

  // INDEXED

  uint8_t ZeroPageIndexedX();

  uint8_t ZeroPageIndexedY();

  uint8_t AbsoluteIndexedX();

  uint8_t AbsoluteIndexedY();

  uint8_t IndexedIndirectX();

  uint8_t IndirectIndexedY();

  // NON-INDEXED

  uint8_t Implicit();

  uint8_t Accumulator();

  uint8_t Immediate();

  uint8_t ZeroPage();

  uint8_t Absolute();

  uint8_t Relative();

  uint8_t Indirect();

  /*-------------------------
   * INTERRUPT HANDLERS
   ------------------------*/

  void NMI() {

  };

  void IRQ() {

  };

  void Reset() {

  };

  /*-------------------------
   * OPCODES
   ------------------------*/

  // Opcodes are declared alphabetically rather than by the type of operation.
  // Easier for me to navigate that way.

  // A - C

  void ADC();

  // D - L

  // N - T
};
