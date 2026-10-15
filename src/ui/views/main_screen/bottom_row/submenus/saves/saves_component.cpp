

#include "saves_component.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"
#include "save_submenus/save_submenu.h"

// ftxui
#include "../roms/roms_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;

//==========================
//
// This namespace is for the saves submenu and any logic that is associated
// with it.
//
// Current memebers: SavesComponent
//
//==========================

namespace SavesComponent {

// Returns controls menu component
Component SavesComponent() {

  // Main container
  return Container::Horizontal({SavesTabMenuComponent() | border,
                                SavesTabContainerComponent() | flex | border}) |

         flex;
};

std::vector<std::string> submenus = {"SRAM", "Save States"};

Component SavesTabContainerComponent() {

  return Container::Tab(

             {
                 SaveSubmenuComponent::SRAMTable,
                 SaveSubmenuComponent::SaveStatesTable,
             },
             &UIState::SelectedSaveMenu) |
         flex;
}

Component SavesTabMenuComponent() {

  return Menu(&submenus, &UIState::SelectedMenu) |
         size(ftxui::WIDTH, ftxui::EQUAL, 15);
}

} // namespace SavesComponent
