
#include "settings_component.h"
#include "../../../../../settings/settings.h"
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

// TODO: i18n, add save button logic, and input verfication, error handling,
// etc, also add a language drop down box, also add a general component that
// just returns Renderer([&] {return text ("")}) for padding

namespace SettingsComponent {

// Returns controls menu component
Component SettingsComponent() {

  // Main container
  return Container::Vertical({

             //************
             // UI OPTIONS
             //************

             Renderer([&] { return text("UI"); }),

             // UI bools

             Renderer([&] { return separator(); }),
             Renderer([&] { return text(""); }),

             Checkbox("Disable colored hotekey info",
                      &Settings::disable_colored_hotkey_info),
             Renderer([&] { return text(""); }),

             Checkbox("Disable ASCII", &Settings::disable_ascii),
             Renderer([&] { return text(""); }),

             GeneralViews::LanguageComponent("Language :", Settings::language),
             Renderer([&] { return text(""); }),

             // Color options

             GeneralViews::ColorComponent("Background color :",
                                          Settings::background_color),
             Renderer([&] { return text(""); }),

             GeneralViews::ColorComponent("Text color :", Settings::text_color),
             Renderer([&] { return text(""); }),

             GeneralViews::ColorComponent("Focus background color :",
                                          Settings::focus_background_color),
             Renderer([&] { return text(""); }),

             GeneralViews::ColorComponent("Focus text color :",
                                          Settings::focus_text_color),
             Renderer([&] { return text(""); }),

             GeneralViews::ColorComponent("ASCII color :",
                                          Settings::ascii_color),
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
                                              Settings::roms_paths),
             Renderer([&] { return text(""); }),

             GeneralViews::TextInputComponent("Default rom path :",
                                              Settings::default_rom_path),
             Renderer([&] { return text(""); }),

             GeneralViews::TextInputComponent("Log path :", Settings::log_path),
             Renderer([&] { return text(""); }),

             GeneralViews::TextInputComponent("SRAM path :",
                                              Settings::sram_path),
             Renderer([&] { return text(""); }),

             GeneralViews::TextInputComponent("Save state path :",
                                              Settings::save_state_path),
             Renderer([&] { return text(""); }),

             Checkbox("Enable detailed logging",
                      &Settings::enable_detailed_logging),
             Renderer([&] { return text(""); }),

             // Save button TODO: implement logic
             Button(
                 "Save", [&] { cout << "test"; }, ButtonOption::Ascii()),

         }) |
         borderEmpty;
}

} // namespace SettingsComponent
