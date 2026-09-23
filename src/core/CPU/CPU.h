

#include <cstdint>
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

  void Branch() {

  };

  bool GetFlag() { return false; };

  void SetFlag() {

  };

  /*-------------------------
   * OPCODES
   ------------------------*/

  /*-------------------------
   * ADDRESSING MODES
   ------------------------*/

  /*-------------------------
   * INTERRUPT HANDLERS
   ------------------------*/

  void NMI() {

  };

  void IRQ() {

  };

  void Reset() {

  };
};
