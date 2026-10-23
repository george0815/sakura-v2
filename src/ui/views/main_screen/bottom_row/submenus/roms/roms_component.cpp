
#include "roms_component.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"
#include <iostream>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

//==========================
//
// Rom Component, as of now just returns a table but as settings are implemented
// and the emulator is built out more behavior will be added
//
// Current memebers: RomTableComponent, StartRom
//
//==========================

// TODO: Implement start rom, i18n

using namespace ftxui;
using namespace std;

namespace RomsComponent {

void StartRom(Component &comp, int index) {

  // Get focused child of internal Container::Vertical in the table
  cout << UIState::SelectedRomTableIndex;
}

// Simple roms table
Component RomTableComponent() {
  return GeneralViews::TableComponent("Name", "Path", "SRAM Data Path", 3,
                                      UIState::SelectedRomTableIndex);
}

} // namespace RomsComponent
