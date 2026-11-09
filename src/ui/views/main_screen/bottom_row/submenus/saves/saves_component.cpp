// this project
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
// Current members: SavesComponent, SavesTabContainerComponent,
// SavesTabMenuComponent
//
//==========================

namespace SavesComponent {

// Returns controls menu component
Component SavesComponent() {

  // Main container, tab menu with the options on the left, main menu on the
  // right, flexed, separated visually with borders
  return Container::Horizontal({SavesTabMenuComponent() | border,
                                SavesTabContainerComponent() | flex | border}) |

         flex;
};

// Tab menu
Component SavesTabMenuComponent() {

  // Initialize here so that i18n is applied
  Submenus = {UIState::I18nObject.tr("SRAM"),
              UIState::I18nObject.tr("Save_States")};

  return Menu(&Submenus, &UIState::SelectedSaveMenu) |
         size(ftxui::WIDTH, ftxui::EQUAL, 20);
}

// Main save menu area, UIState::SelectedSaveMenu holds whatever tab is
// selected
Component SavesTabContainerComponent() {

  // Tables are set here so the 18n strings can be applied
  SaveSubmenuComponent::SRAMTable =
      SaveSubmenuComponent::SaveSRAMTableComponent();
  SaveSubmenuComponent::SaveStatesTable =
      SaveSubmenuComponent::SaveStateTableComponent();

  return Container::Tab(

             {
                 SaveSubmenuComponent::SRAMTable,
                 SaveSubmenuComponent::SaveStatesTable,
             },
             &UIState::SelectedSaveMenu) |
         flex;
}

} // namespace SavesComponent
