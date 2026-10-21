#include "controls_component.h"
#include "../../../../../settings/settings.h"
#include "../../../../general/general_views.h"
#include "SDL3/SDL_keyboard.h"
#include <SDL3/SDL_keycode.h>
#include <ftxui/component/event.hpp>
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

// Converts a SDL3 keycode to one that can be easily used by FTXUI. This
// function is called whenever settings are being deserialized from JSON. It's
// only really used to set the button label, so returning a string is fine.

// TODO:: Test against edge cases

string KeyCodeToFTXUI(int code) {

  // convert from 32 bit int
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

} // namespace ControlsComponent
