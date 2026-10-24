

#include "save_submenu.h"
#include "../../../../../../state.h"
#include "../../../../../general/general_views.h"

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
// Save submenu compenents, contains two table compenents, one for
// save states and one for SRAM
//
// Current memebers: SaveSubmenuComponent, SaveSRAMTableComponent
//
//==========================

// TODO: i18n

using namespace ftxui;
using namespace std;

namespace SaveSubmenuComponent {

// Table for save states
Component SaveStateTableComponent() {
  return GeneralViews::TableComponent("Name", "Created", "Size", 10,
                                      UIState::SelectedSaveStateTableIndex);
}

// Table for SRAM
Component SaveSRAMTableComponent() {
  return GeneralViews::TableComponent("Name", "Created", "Size", 10,
                                      UIState::SelectedSRAMTableIndex);
}

} // namespace SaveSubmenuComponent
