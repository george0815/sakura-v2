

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
// Current memebers: SavesComponent, SavesTabContainerComponent,
// SavesTabMenuComponent
//
//==========================

// TODO: i18n, implement open save state folder/open SRAM folder logic

namespace SavesComponent {

// Returns controls menu component
Component SavesComponent() {

  // Main container, tab menu with the options on the left, main menu on the
  // right, flexed, separated visually with borders
  return Container::Horizontal({SavesTabMenuComponent() | border,
                                SavesTabContainerComponent() | flex | border}) |

         flex;
};

// Options for the tab menu
std::vector<std::string> submenus = {"SRAM", "Save States"};

// Tab menu
Component SavesTabMenuComponent() {

  return Menu(&submenus, &UIState::SelectedSaveMenu) |
         size(ftxui::WIDTH, ftxui::EQUAL, 15);
}

// Main save menu area, UIState::SelectedSaveMenu holds whatever tab is
// selected
Component SavesTabContainerComponent() {

  return Container::Tab(

             {
                 SaveSubmenuComponent::SRAMTable,
                 SaveSubmenuComponent::SaveStatesTable,
             },
             &UIState::SelectedSaveMenu) |
         flex;
}

} // namespace SavesComponent
