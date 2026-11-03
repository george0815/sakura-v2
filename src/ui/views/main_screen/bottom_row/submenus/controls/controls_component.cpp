// this project
#include "controls_component.h"
#include "../../../../../settings/settings.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"

// SDL3
#include "SDL3/SDL_keyboard.h"
#include <SDL3/SDL_keycode.h>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;

//==========================
//
// This namespace is for the controls submenu and any logic that is associated
// with it.
//
// Current memebers: ControlsComponent, KeyCodeToSDL3, KeyCodeToFTXUI
//
//==========================

using namespace GeneralViews; // Components
using namespace UIState;      // labels, i18n_object
using namespace Settings;     // Controls

namespace ControlsComponent {

// Returns controls menu component
Component ControlsComponent() {

  // Main container
  return Container::Vertical({

             // START AND STOP
             ControlOptionComponent(i18n_object.tr("Start_rom:_"),
                                    start_rom_control, start_rom_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("Stop_rom:_"),
                                    stop_rom_control, stop_rom_label),
             Padding(),

             // FOLDERS
             ControlOptionComponent(i18n_object.tr("Open_rom_folder:_"),
                                    open_rom_folder_control,
                                    open_rom_folder_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("Open_SRAM_folder:_"),
                                    open_sram_folder_control,
                                    open_SRAM_folder_label),
             Padding(),

             // SAVING
             ControlOptionComponent(i18n_object.tr("Save_state:_"),
                                    save_state_control, save_state_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("Load_state:_"),
                                    load_state_control, load_state_label),
             Padding(),

             // CONTROLLER BUTTONS
             ControlOptionComponent(i18n_object.tr("START:_"), start_control,
                                    start_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("SELECT:_"), select_control,
                                    select_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("A:_"), a_control, a_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("B:_"), b_control, b_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("UP:_"), up_control,
                                    up_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("DOWN:_"), down_control,
                                    down_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("LEFT:_"), left_control,
                                    left_label),
             Padding(),

             ControlOptionComponent(i18n_object.tr("RIGHT:_"), right_control,
                                    right_label),
             Padding(),

             Renderer([&] { return separator(); }),

             // SAVE BUTTON
             Button(
                 i18n_object.tr("Save"), [&] { save_settings(false); },
                 ButtonOption::Ascii()),

         }) |
         borderEmpty;
}

// Converts a SDL3 keycode to one that can be easily used by FTXUI. This
// function is called whenever settings are being deserialized from JSON. It's
// only really used to set the button label, so returning a string is fine.

// TODO:: Test against edge cases

string KeyCodeToFTXUI(int code) {

  // Convert from 32 bit int
  SDL_Keycode tmp_code = (SDL_Keycode)code;

  return SDL_GetKeyName(tmp_code);
}

// Converts a FTXUI keycode to one that can be easily used by SDL3. This
// function is called whenever settings are being serialized to JSON.

int KeyCodeToSDL3(const ftxui::Event &key_event) {

  // Normal characters
  if (key_event.is_character()) {

    string input = key_event.character();
    char c = input[0];

    return (int)(c);
  }

  // Special characters (unfortunately key_event needs to be an int to use a
  // switch)

  // Special
  if (key_event == Event::Escape) {
    return SDLK_ESCAPE;
  }
  if (key_event == Event::Return) {
    return SDLK_RETURN;
  }
  if (key_event == Event::Tab) {
    return SDLK_TAB;
  }
  if (key_event == Event::Backspace) {
    return SDLK_BACKSPACE;
  }
  if (key_event == Event::Delete) {
    return SDLK_DELETE;
  }

  // Arrow keys
  if (key_event == Event::ArrowUp) {
    return SDLK_UP;
  }
  if (key_event == Event::ArrowDown) {
    return SDLK_DOWN;
  }
  if (key_event == Event::ArrowLeft) {
    return SDLK_LEFT;
  }
  if (key_event == Event::ArrowRight) {
    return SDLK_RIGHT;
  }

  // Nav keys
  if (key_event == Event::Home) {
    return SDLK_HOME;
  }
  if (key_event == Event::End) {
    return SDLK_END;
  }
  if (key_event == Event::PageUp) {
    return SDLK_PAGEUP;
  }
  if (key_event == Event::PageDown) {
    return SDLK_PAGEDOWN;
  }

  // Function keys
  if (key_event == Event::F1) {
    return SDLK_F1;
  }
  if (key_event == Event::F2) {
    return SDLK_F2;
  }
  if (key_event == Event::F3) {
    return SDLK_F3;
  }
  if (key_event == Event::F4) {
    return SDLK_F4;
  }
  if (key_event == Event::F5) {
    return SDLK_F5;
  }
  if (key_event == Event::F6) {
    return SDLK_F6;
  }
  if (key_event == Event::F7) {
    return SDLK_F7;
  }
  if (key_event == Event::F8) {
    return SDLK_F8;
  }
  if (key_event == Event::F9) {
    return SDLK_F9;
  }
  if (key_event == Event::F10) {
    return SDLK_F10;
  }
  if (key_event == Event::F11) {
    return SDLK_F11;
  }
  if (key_event == Event::F12) {
    return SDLK_F12;
  }

  // Default
  return SDLK_UNKNOWN;
}

// Used for normalizing the control strings
string ToUpper(string lower) {

  string upper = "";

  for (char c : lower) {
    upper += toupper(c);
  }

  return upper;
}

} // namespace ControlsComponent
