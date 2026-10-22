#include "../core/CPU/CPU.h"
#include "./settings/settings.h"
#include "state.h"
#include "views/general/general_views.h"
#include "views/main_screen/bottom_row/bottom_row_component.h"
#include "views/main_screen/bottom_row/submenus/log/log_component.h"
#include "views/main_screen/bottom_row/submenus/roms/roms_component.h"
#include "views/main_screen/main_screen.h"
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <i18ncpp.h>
#include <iostream>

using namespace ftxui;
using namespace std;

// stub for parseRom function
void parseRom(string &value) {
  value = "CHANGED";
  cout << "Parsing rom...";
}

void ExitScreen(ScreenInteractive &screen) { screen.Exit(); }

int main() {

  // TODO: 1. Backup settigns, since this is done before the json is parse it
  // should be all safe default values. 2. Try laoding config file, 3. If it
  // fails, load backup

  if (Settings::load_settings() != 0) {

    // TODO: Finish this function

    // 1. Save default settings
    Settings::save_settings(); // TODO: Create save default settings function

    Settings::load_settings();
  }

  // Delare hardware components
  CPU *cpu = new CPU();

  // Declare screen, ScreenInteractive::Fullscreen uses the entire terminal
  // window
  ScreenInteractive screen = ScreenInteractive::Fullscreen();
  screen.TrackMouse(true); // Track mouse input
  screen.CaptureMouse();   // TODO: Check if this is redundant

  // Set Fullscreen
  screen.Fullscreen(); // TODO: Check if this is redundant

  // Declare main loop, originally I did screen.Loop but decalring the loop
  // separately allows for greater control and for me to react to changes in
  // global variables that I set
  Loop loop(&screen,
            MainScreen::MainScreenComponent() | border | color(Color::White));

  // Main loop
  while (!loop.HasQuitted()) {

    // If exit flag is set
    if (UIState::Exit == true) {

      // Save settings
      if (Settings::save_settings() == 0) {

        ExitScreen(screen);
      }
    }
    loop.RunOnce();
  }

  return EXIT_SUCCESS;
}
