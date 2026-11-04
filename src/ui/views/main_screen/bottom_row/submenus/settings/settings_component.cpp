
#include "settings_component.h"
#include "../../../../../settings/settings.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"
#include <iostream>

// ftxui
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;
using namespace filesystem;

//==========================
//
// This namespace is for the settings submenu and any logic that is associated
// with it.
//
// Current members: SettingsComponent
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
                      &Settings::DisableColoredHotkeyInfo),
             Renderer([&] { return text(""); }),

             Checkbox("Disable ASCII", &Settings::DisableASCII),
             Renderer([&] { return text(""); }),

             GeneralViews::LanguageComponent("Language :", Settings::Language),
             Renderer([&] { return text(""); }),

             // Color options

             GeneralViews::ColorComponent("Background color :",
                                          Settings::BackgroundColor),
             Renderer([&] { return text(""); }),

             GeneralViews::ColorComponent("Text and border color :",
                                          Settings::TextAndBorderColor),
             Renderer([&] { return text(""); }),

             GeneralViews::ColorComponent("ASCII color :",
                                          Settings::ASCIIColor),
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
                                              Settings::RomsPaths),
             Renderer([&] { return text(""); }),

             GeneralViews::TextInputComponent("Default rom path :",
                                              Settings::DefaultRomPath),
             Renderer([&] { return text(""); }),

             GeneralViews::TextInputComponent("Log path :", Settings::LogPath),
             Renderer([&] { return text(""); }),

             GeneralViews::TextInputComponent("SRAM path :",
                                              Settings::SRAMPath),
             Renderer([&] { return text(""); }),

             GeneralViews::TextInputComponent("Save state path :",
                                              Settings::SaveStatePath),
             Renderer([&] { return text(""); }),

             Checkbox("Enable detailed logging",
                      &Settings::EnableDetailedLogging),
             Renderer([&] { return text(""); }),

             // Save button TODO: implement logic
             Button(
                 "Save", [&] { cout << "test"; }, ButtonOption::Ascii()),

         }) |
         borderEmpty;
}

} // namespace SettingsComponent
