// this project
#include "../core/CPU/CPU.h"
#include "./settings/settings.h"
#include "state.h"
#include "views/general/general_views.h"
#include "views/main_screen/bottom_row/bottom_row_component.h"
#include "views/main_screen/bottom_row/submenus/log/log_component.h"
#include "views/main_screen/bottom_row/submenus/roms/roms_component.h"
#include "views/main_screen/main_screen.h"

// std and misc
#include <cstdlib>
#include <filesystem>
#include <i18ncpp.h>

// ftxui
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

using namespace ftxui;    // Compoennts and elements
using namespace Settings; // load_settings, save_settings
using namespace UIState;  // i18n_object
using namespace std;

void ExitScreen(ScreenInteractive &screen) { screen.Exit(); }

int main() {

  // Save backup of settings TODO: Low priority: use some sort of hash or
  // something to detect if the backup has been change to limit unnecessaru
  // writes
  save_settings(true);

  // If no config file exists, create one
  filesystem::path tmp_config_path = "config.ini";
  if (!filesystem::exists(tmp_config_path)) {
    save_settings(false);
  }

  // If loading main fails, load backup we just created
  if (load_settings(false) != 0) {
    load_settings(true);
  }

  // Set up i18n
  i18n_object.loadLocaleFromFile("en.json");
  i18n_object.loadLocaleFromFile("jp.json");
  i18n_object.setLocale(locale_entries[language]);

  // Delare hardware components
  // LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent,
  //                         i18n_object.tr("sakura_init"));
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
  Loop loop(&screen, MainScreen::MainScreenComponent() | border |
                         color(colors[text_and_border_color]) |
                         bgcolor(colors[background_color]));

  // Main loop
  while (!loop.HasQuitted()) {

    // If exit flag is set
    if (Exit == true) {

      // Save settings
      if (save_settings(false) == 0) {
        ExitScreen(screen);
      }
    }
    loop.RunOnce();
  }

  return EXIT_SUCCESS;
}
