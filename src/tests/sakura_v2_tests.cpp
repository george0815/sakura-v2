#include "../core/CART/CART.h"
#include "../core/CPU/CPU_6502.h"
#include "../ui/state.h"
#include <cassert>
#include <iostream>

/*
 * I was wondering how I was going to implement tests for the CPU and I
 * eventually landed on this.
 *
 * - Tests for helper functions such as the flag helper functions
 * - For opcodes/addresssing modes, I will load nestest.nes, and compare
 * the state of the CPU at a given instruction to the state of the CPU at the
 * same instruction in nestest.log. (A log of nestest.nes running on an accurate
 * emulator.)
 *
 * - For the CART, I will have it load some well-known roms and compare it to
 * its known values (for ex, load Super Mario Bros 3 and assert MAPPER_NUMBER
 * == 4).
 *
 * - Still wondering on what to do for the PPU but that's a problem for a future
 * Hunter
 * */

using namespace std;     // cout
using namespace UIState; // cout
int main() {

  //===============================
  // CART TESTS
  //===============================

  // Set up i18n
  I18nObject.loadLocaleFromFile("en.json");
  I18nObject.loadLocaleFromFile("jp.json");
  I18nObject.setLocale(LocaleEntries[0]); // english, 1 for japanese

  // Rom paths
  string smb = "roms/smb.nes";
  string smb3 = "roms/smb3.nes";
  string ng3 = "roms/ng3.nes";

  cout << "STARTING CART TESTS...\n" << endl;

  // SUPER MARIO BROS.
  cout << "\nSUPER MARIO BROS....\n" << endl;
  CART *cartridge = new CART();
  cartridge->READ_ROM(smb);

  assert(cartridge->PRG_ROM_SIZE == 0x8000);
  assert(cartridge->CHR_ROM_SIZE == 0x2000);
  assert(cartridge->MAPPER_NUMBER == 0x0);
  assert(cartridge->NAMETABLE_MIRRORING == CART::NAMETABLE_MIRRORING::VERTICAL);

  // SUPER MARIO BROS 3.
  cout << "\nSUPER MARIO BROS. 3...\n" << endl;
  cartridge = new CART();
  cartridge->READ_ROM(smb3);

  assert(cartridge->PRG_ROM_SIZE == 0x40000);
  assert(cartridge->CHR_ROM_SIZE == 0x20000);
  assert(cartridge->MAPPER_NUMBER == 0x4);
  assert(cartridge->NAMETABLE_MIRRORING ==
         CART::NAMETABLE_MIRRORING::HORIZONTAL);

  // NINJA GAIDEN
  cout << "\nNINJA GAIDEN 3...\n" << endl;
  cartridge = new CART();
  cartridge->READ_ROM(ng3);

  assert(cartridge->PRG_ROM_SIZE == 0x20000);
  assert(cartridge->CHR_ROM_SIZE == 0x20000);
  assert(cartridge->MAPPER_NUMBER == 0x4);
  // Ninja Gaiden's nametable mirroring is entirely controllered by mapper 4,
  // thus no assert here.

  //===============================
  // FLAG TESTS
  //===============================

  cout << "\nSTARTING CPU TESTS...\n" << endl;

  cout << "\nFLAG TESTS...\n" << endl;
  CPU_6502 *test_cpu = new CPU_6502();

  // INTERRUPT DISABLE

  // For running the test without CMake
  cout << "\nSET INT DISABLE...";
  test_cpu->SET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE);
  cout << "\nINT DISABLE: " +
              to_string(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE));

  // Assert
  assert(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE));

  // For running the test without CMake
  cout << "\nCLEAR INT DISABLE...";
  test_cpu->CLEAR_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE);
  cout << "\nINT DISABLE: " +
              to_string(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE))
       << endl;

  // Assert
  assert(!test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE));

  // CARRY

  // For running the test without CMake
  cout << "\nSET CARRY...";
  test_cpu->SET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE);
  cout << "\nCARRY: " +
              to_string(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE));

  // Assert
  assert(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE));

  // For running the test without CMake
  cout << "\nCLEAR CARRY...";
  test_cpu->CLEAR_FLAG(CPU_6502::STATUS_FLAG::CARRY);
  cout << "\nCARRY: " +
              to_string(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::CARRY))
       << endl;

  // Assert
  assert(!test_cpu->GET_FLAG(!CPU_6502::STATUS_FLAG::CARRY));

  // OVERFLOW

  // For running the test without CMake
  cout << "\nSET OVERFLOW...";
  test_cpu->SET_FLAG(CPU_6502::STATUS_FLAG::OVERFLOW);
  cout << "\nOVERFLOW: " +
              to_string(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::OVERFLOW));

  // Assert
  assert(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::OVERFLOW));

  // For running the test without CMake
  cout << "\nCLEAR OVERFLOW...";
  test_cpu->CLEAR_FLAG(CPU_6502::STATUS_FLAG::OVERFLOW);
  cout << "\nOVERFLOW: " +
              to_string(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::OVERFLOW))
       << endl;

  // Assert
  assert(!test_cpu->GET_FLAG(!CPU_6502::STATUS_FLAG::OVERFLOW));

  return 0;
}
