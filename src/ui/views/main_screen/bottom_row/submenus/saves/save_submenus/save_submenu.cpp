

#include "save_submenu.h"
#include "../../../../../general/general_views.h"
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
// Current memebers: RomTableComponent
//
//==========================

using namespace ftxui;
using namespace std;

// Simple roms table
Component SaveSubmenuComponent::SaveTableComponent() {
  return GeneralViews::TableComponent("Name", "Created", "Size", 10);
}
