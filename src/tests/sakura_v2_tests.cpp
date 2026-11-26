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

  // SUPER MARIO BROS 3.
  cout << "\nSUPER MARIO BROS. 3...\n" << endl;
  cartridge = new CART();
  cartridge->READ_ROM(smb3);

  // NINJA GAIDEN 3
  cout << "\nNINJA GAIDEN 3...\n" << endl;
  cartridge = new CART();
  cartridge->READ_ROM(ng3);

  //===============================
  // FLAG TESTS
  //===============================

  CPU_6502 *test_cpu = new CPU_6502();

  test_cpu->SET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE);
  assert(test_cpu->GET_FLAG(CPU_6502::STATUS_FLAG::INT_DISABLE));
  return 0;
}
