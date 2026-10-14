#include "../../../state.h"
#include "../main_screen.h"
#include "bottom_row_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
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

/* TODO: PADDING, COLOR
 * COMMENTS
 * GET VALUES FROM SETTINGS CONFIG / VARIABLES*/

using namespace ftxui;

ButtonOption Style() {
  auto option = ButtonOption::Ascii();
  return option;
};

std::vector<std::string> submenus = {"Roms", "Saves", "Settings", "Controls",
                                     "log"};

Component BottomRow::TabContainerComponent() {

  return Container::Tab(

             {

                 RomsComponent::RomSubmenuComponent,
                 SavesComponent::SavesSubmenuComponent,
                 SettingsComponent::SettingsSubmenuComponent |
                     vscroll_indicator | frame,
                 ControlsComponent::ControlsSubmenuComponent,
                 LogComponent::LogSubmenuComponent,

             },
             &UIState::SelectedMenu) |
         flex;
}

Component BottomRow::TabMenuComponent() {

  return Container::Vertical({
      Menu(&submenus, &UIState::SelectedMenu) |
          size(ftxui::WIDTH, ftxui::GREATER_THAN, 18) | flex,

      Button(
          " Exit ", [&] { UIState::Exit = true; }, Style()) |
          center | size(ftxui::HEIGHT, ftxui::LESS_THAN, 3) | borderEmpty,

  });
}
