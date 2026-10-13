
#include "settings_component.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"
#include <ftxui/component/captured_mouse.hpp>
#include <iostream>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;

//==========================
//
// This namespace is for the settings submenu and any logic that is associated
// with it.
//
// Current memebers: SettingsComponent
//
//==========================

namespace SettingsComponent {

bool test = false;

// Returns controls menu component
Component SettingsComponent() {

  // Main container
  return Container::Vertical(
             {

                 //************
                 // UI OPTIONS
                 //************

                 Renderer([&] {
                   return text("UI");
                 }), // Disabled colored hotkey info, hide text cursor, bg
                     // color,
                     // text color, focus background color, focus text color,
                     // ascii color, diable ascii
                 Renderer([&] { return separator(); }),
                 Renderer([&] { return text(""); }),

                 Checkbox("Disable colored hotekey info", &test),
                 Renderer([&] { return text(""); }),

                 Checkbox("Hide text cursor", &test),
                 Renderer([&] { return text(""); }),

                 Checkbox("Disable ASCII", &test),
                 Renderer([&] { return text(""); }),

                 // Color options

                 GeneralViews::ColorComponent("Background color :", 0,
                                              UIState::TestColorSelection),
                 Renderer([&] { return text(""); }),

                 GeneralViews::ColorComponent("Text color :", 0,
                                              UIState::TestColorSelection),
                 Renderer([&] { return text(""); }),

                 GeneralViews::ColorComponent("Focus background color :", 0,
                                              UIState::TestColorSelection),
                 Renderer([&] { return text(""); }),

                 GeneralViews::ColorComponent("Focus text color :", 0,
                                              UIState::TestColorSelection),
                 Renderer([&] { return text(""); }),

                 GeneralViews::ColorComponent("ASCII color :", 0,
                                              UIState::TestColorSelection),
                 Renderer([&] { return text(""); }),

                 //************
                 // SYSTEM OPTIONS
                 //************

                 Renderer([&] {
                   return text("System");
                 }), // Roms paths, Default rom path, Log path, SRAM path, save
                     // state path, Enable detailed logging
                 Renderer([&] { return separator(); }),

                 Renderer([&] { return text(""); }),
                 GeneralViews::TextInputComponent("Roms paths :",
                                                  UIState::TestTextValue),
                 Renderer([&] { return text(""); }),

                 GeneralViews::TextInputComponent("Default rom path :",
                                                  UIState::TestTextValue),
                 Renderer([&] { return text(""); }),

                 GeneralViews::TextInputComponent("Log path :",
                                                  UIState::TestTextValue),
                 Renderer([&] { return text(""); }),

                 GeneralViews::TextInputComponent("SRAM path :",
                                                  UIState::TestTextValue),
                 Renderer([&] { return text(""); }),

                 GeneralViews::TextInputComponent("Save state path :",
                                                  UIState::TestTextValue),
                 Renderer([&] { return text(""); }),

                 Checkbox("Disable ASCII", &test),
                 Renderer([&] { return text(""); }),

                 // Save button
                 Button(
                     "Save", [&] { cout << "test"; }, ButtonOption::Ascii()),

             },
             &UIState::TestSelectedIndex) |
         borderEmpty;
}

} // namespace SettingsComponent
