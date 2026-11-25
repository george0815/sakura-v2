

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
  CPU();

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

  enum STATUS_FLAG {

    CARRY = 0,
    ZERO = 1,
    INT_DISABLE = 2,
    DEC = 3,
    B_FLAG = 4,
    // The 6th bit has not effect, technically neither does the b flag but the
    // 6th is literally always pushed as 1
    OVERFLOW = 6,
    NEG = 7
  };

  /*-------------------------
   * INTERRUPT VECTORS
   ------------------------*/

  // The vectors are basically the location that the CPU jumps to when a given
  // interrupt occurs. For example in the case of a IRQ it will generally read a
  // new PC from FFFE - FFFF, the execute from there.

  uint16_t RESET_VECTOR = 0xFFFC;
  uint16_t IRQ_VECTOR = 0xFFFE;
  uint16_t NMI_VECTOR = 0xFFFA;

  /*-------------------------
   * HELPER FUNCTIONS
   ------------------------*/

  void BRANCH();

  bool GET_FLAG(int flag);

  void SET_FLAG(int flag);

  void CLEAR_FLAG(int flag);

  /*-------------------------
   * ADDRESSING MODES
   ------------------------*/

  // INDEXED

  uint16_t ZERO_PAGE_INDEXED_X();

  uint16_t ZERO_PAGE_INDEXED_Y();

  uint16_t ABSOLUTE_INDEXED_X();

  uint16_t ABSOLUTE_INDEXED_Y();

  uint16_t INDEXED_INDIRECT_X();

  uint16_t INDIRECT_INDEXED_Y();

  // NON-INDEXED

  uint16_t IMPLICIT();

  uint16_t ACCUMULATOR();

  uint16_t IMMEDIATE();

  uint16_t ZERO_PAGE();

  uint16_t ABSOLUTE();

  uint16_t RELATIVE();

  uint16_t INDIRECT();

  /*-------------------------
   * INTERRUPT HANDLERS
   ------------------------*/

  void NMI();

  void IRQ() {

  };

  void RESET() {

  };

  /*-------------------------
   * OPCODES
   ------------------------*/

  // Opcodes are declared alphabetically rather than by the type of operation.
  // Easier for me to navigate that way.

  // A - C

  void ADC(uint16_t addr);

  // D - L

  // N - T
};
