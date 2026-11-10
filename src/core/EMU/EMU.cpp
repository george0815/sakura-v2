#include "EMU.h"
#include "../../ui/views/main_screen/bottom_row/submenus/log/log_component.h"
#include "../CART/CART.h"

int EMU::START_ROM(string file_name) {

  CART *cartridge = new CART();

  cartridge->READ_ROM(file_name);

  return 0;
}
