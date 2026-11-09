// this project
#include "../../../state.h"
#include "../main_screen.h"
#include "bottom_row_component.h"

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

// submenus
#include "submenus/controls/controls_component.h"
#include "submenus/log/log_component.h"
#include "submenus/roms/roms_component.h"
#include "submenus/saves/saves_component.h"
#include "submenus/settings/settings_component.h"

//==========================
//
// This namespace is for the bottom row/tab components and any logic that is
// associated with them.
//
// Current members: TabContainerComponent, TabMenuComponent
//
//==========================

/* TODO: PADDING, COLOR
 * COMMENTS
 * GET VALUES FROM SETTINGS CONFIG / VARIABLES, i18n, start rom logic */

using namespace ftxui;
using namespace std;
using namespace UIState; // SelectedMenu, I18nObject

// Menu tab options
std::vector<std::string> submenus;

namespace BottomRow {

// Main menu contents that displays on the right side of the screen
Component TabContainerComponent() {

  // Set components in function rather in at the namespace scope so that text
  // can be properly translated (if I don't do this then the submenu component
  // varibles will be set before the local is properly set) (NOTE:
  // RomSubmenuComponent is set in InitializedRomComponent)
  SettingsComponent::SettingsSubmenuComponent =
      SettingsComponent::SettingsComponent();
  LogComponent::LogSubmenuComponent = LogComponent::LogComponent();
  SavesComponent::SavesSubmenuComponent = SavesComponent::SavesComponent();
  ControlsComponent::ControlsSubmenuComponent =
      ControlsComponent::ControlsComponent();

  // Main content
  return Container::Tab(

             // vscroll_indicator and frame is needed for scrolling TODO: fix
             // glitch where scrolling is enabled only after clicking on a
             // dropdown or input
             {

                 RomsComponent::InitializedRomComponent() | vscroll_indicator |
                     frame,
                 SavesComponent::SavesSubmenuComponent | vscroll_indicator |
                     frame,
                 SettingsComponent::SettingsSubmenuComponent |
                     vscroll_indicator | frame,
                 ControlsComponent::ControlsSubmenuComponent |
                     vscroll_indicator | frame,
                 LogComponent::LogSubmenuComponent | vscroll_indicator | frame,

             },
             &SelectedMenu) |
         flex;
}

// Menu that displays on the left side of the screen
Component TabMenuComponent() {

  // Menu options
  submenus = {I18nObject.tr("Roms"), I18nObject.tr("Saves"),
              I18nObject.tr("Settings"), I18nObject.tr("Controls"),
              I18nObject.tr("Log")};

  return Container::Vertical({

      // Menu with options
      Menu(&submenus, &SelectedMenu) |
          size(ftxui::WIDTH, ftxui::GREATER_THAN, 18) | flex,

      // Exit button, rather than having exit logic here, sets a flag that is
      // observed in the main loop
      Button(
          " " + I18nObject.tr("Exit") + " ", [&] { Exit = true; },
          ButtonOption::Ascii()) |
          center | size(ftxui::HEIGHT, ftxui::LESS_THAN, 3) | borderEmpty,

  });
}

} // namespace BottomRow
