#include "../../../state.h"
#include "../main_screen.h"
#include "bottom_row_component.h"
#include <iostream>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

// Submenus
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
// Current memebers: TabContainerComponent, TabMenuComponent
//
//==========================

/* TODO: PADDING, COLOR
 * COMMENTS
 * GET VALUES FROM SETTINGS CONFIG / VARIABLES, i18n, start rom logic */

using namespace ftxui;

// Menu tab options
std::vector<std::string> submenus;

namespace BottomRow {

// Main menu contents that displays on the right side of the screen
Component TabContainerComponent() {

  // Set components in function rather in at the namespace scope so that text
  // can be properly translated (if I don't do this then the submenu component
  // varibles will be set before the local is properly set)
  RomsComponent::RomSubmenuComponent = RomsComponent::RomTableComponent();
  SettingsComponent::SettingsSubmenuComponent =
      SettingsComponent::SettingsComponent();
  LogComponent::LogSubmenuComponent = LogComponent::LogComponent();
  SavesComponent::SavesSubmenuComponent = SavesComponent::SavesComponent();
  ControlsComponent::ControlsSubmenuComponent =
      ControlsComponent::ControlsComponent();

  // Load roms
  RomsComponent::LoadAllRoms();

  // Wraps roms component in CatchEvent so that it can respond to key presses
  // (for launching the rom from the table, opening folders, etc)
  auto wrapped_roms =
      CatchEvent(RomsComponent::RomSubmenuComponent, [](Event event) {
        // This was me testing  // TODO: read actual controls and implement
        // proper logic
        if (event == Event::F3 || event == Event::Return) {
          RomsComponent::StartRom();
        }
        return false;
      });

  // Main content
  return Container::Tab(

             // vscroll_indicator and frame is needed for scrolling TODO: fix
             // glitch where scrolling is eabled only after clicking on a
             // dropdown or input
             {

                 wrapped_roms | vscroll_indicator | frame,
                 SavesComponent::SavesSubmenuComponent | vscroll_indicator |
                     frame,
                 SettingsComponent::SettingsSubmenuComponent |
                     vscroll_indicator | frame,
                 ControlsComponent::ControlsSubmenuComponent |
                     vscroll_indicator | frame,
                 LogComponent::LogSubmenuComponent | vscroll_indicator | frame,

             },
             &UIState::SelectedMenu) |
         flex;
}

// Menu that displays on the left side of the screen
Component TabMenuComponent() {

  submenus = {UIState::i18_object.tr("Roms"), UIState::i18_object.tr("Saves"),
              "Settings", "Controls", "log"};

  return Container::Vertical({

      // Menu with options
      Menu(&submenus, &UIState::SelectedMenu) |
          size(ftxui::WIDTH, ftxui::GREATER_THAN, 18) | flex,

      // Exit button, rather than having exit logic here, sets a flag that is
      // observed in the main loop
      Button(
          " Exit ", [&] { UIState::Exit = true; }, ButtonOption::Ascii()) |
          center | size(ftxui::HEIGHT, ftxui::LESS_THAN, 3) | borderEmpty,

  });
}

} // namespace BottomRow
