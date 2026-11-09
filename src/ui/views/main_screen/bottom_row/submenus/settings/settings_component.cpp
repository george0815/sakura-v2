
#include "settings_component.h"
#include "../../../../../settings/settings.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"

// ftxui
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;
using namespace filesystem;
using namespace GeneralViews; // LanguageComponent, ColorComponent, Padding
using namespace Settings; // DisableColoredHotkeyInfo, DisableASCII, Language,
                          // BackgroundColor, TextAndBorderColor, ASCIIColor,
                          // RomsPaths, DefaultRomPath, LogPath,
                          // EnableDetailedLogging, SRAMPath, SaveStatePath
using namespace UIState;  // I18nObject

//==========================
//
// This namespace is for the settings submenu and any logic that is associated
// with it.
//
// Current members: SettingsComponent
//
//==========================

// TODO: i18n
namespace SettingsComponent {

// Returns controls menu component
Component SettingsComponent() {

  // Main container
  return Container::Vertical({

             //************
             // UI OPTIONS
             //************

             Renderer([&] { return text(I18nObject.tr("UI")); }),

             // UI bools

             Renderer([&] { return separator(); }),
             Padding(),

             Checkbox(I18nObject.tr("Disable_colored_hotkey_information"),
                      &DisableColoredHotkeyInfo),
             Padding(),

             Checkbox(I18nObject.tr("Disable_ASCII"), &DisableASCII),
             Padding(),

             GeneralViews::LanguageComponent(I18nObject.tr("Language:_"),
                                             Language),
             Padding(),

             // Color options

             GeneralViews::ColorComponent(I18nObject.tr("Background_color:_"),
                                          BackgroundColor),
             Padding(),

             GeneralViews::ColorComponent(
                 I18nObject.tr("Text_and_border_color:_"), TextAndBorderColor),
             Padding(),

             GeneralViews::ColorComponent(I18nObject.tr("ASCII_color:_"),
                                          ASCIIColor),
             Padding(),

             //************
             // SYSTEM OPTIONS
             //************

             Renderer([&] {
               return text("System");
             }), // Roms paths, Default rom path, Log path, SRAM path, save
                 // state path, Enable detailed logging
             Padding(),
             Renderer([&] { return separator(); }),

             GeneralViews::TextInputComponent(I18nObject.tr("Roms_paths:_"),
                                              RomsPaths),
             Padding(),

             GeneralViews::TextInputComponent(
                 I18nObject.tr("Default_rom_path:_"), DefaultRomPath),
             Padding(),

             GeneralViews::TextInputComponent(I18nObject.tr("Log_path:_"),
                                              LogPath),
             Padding(),

             GeneralViews::TextInputComponent(I18nObject.tr("SRAM_path:_"),
                                              SRAMPath),
             Padding(),

             GeneralViews::TextInputComponent(
                 I18nObject.tr("Save_state_path:_"), SaveStatePath),
             Padding(),

             Checkbox(I18nObject.tr("Enable_detailed_logging"),
                      &EnableDetailedLogging),
             Padding(),

             // Save button TODO: implement logic
             Button(
                 I18nObject.tr("Save"), [&] { SaveSettings(false); },
                 ButtonOption::Ascii()),

         }) |
         borderEmpty;
}

} // namespace SettingsComponent
