#include "controls_component.h"
#include "../../../../../settings/settings.h"
#include "../../../../general/general_views.h"
#include <iostream>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;

//==========================
//
// This namespace is for the controls submenu and any logic that is associated
// with it.
//
// Current memebers: ControlsComponent
//
//==========================

namespace ControlsComponent {

// Returns controls menu component
Component ControlsComponent() {

  // Main container
  return Container::Vertical({

             GeneralViews::ControlOptionComponent("Start rom :",
                                                  Settings::start_rom_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("Stop rom :",
                                                  Settings::stop_rom_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent(
                 "Open rom folder :", Settings::open_rom_folder_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent(
                 "Open SRAM folder :", Settings::open_sram_folder_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("Save state :",
                                                  Settings::save_state_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("Load state :",
                                                  Settings::load_state_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("START :",
                                                  Settings::start_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("SELECT :",
                                                  Settings::select_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("A :", Settings::a_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("B :", Settings::b_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("UP :", Settings::up_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("DOWN :",
                                                  Settings::down_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("LEFT :",
                                                  Settings::left_control),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("RIGHT :",
                                                  Settings::right_control),
             Renderer([&] { return text(""); }),
             Renderer([&] { return separator(); }),

             // Save button
             Button(
                 "Save", [&] { cout << "test"; }, ButtonOption::Ascii()),

         }) |
         borderEmpty;
}

} // namespace ControlsComponent
