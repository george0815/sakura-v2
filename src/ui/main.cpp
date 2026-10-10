#include "../core/CPU/CPU.h"
#include "views/main_screen/main_screen.h"
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
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

  CPU *cpu = new CPU();

  ScreenInteractive screen = ScreenInteractive::Fullscreen();

  screen.CaptureMouse();
  screen.Fullscreen();

  Loop loop(&screen, MainScreen::MainScreenComponent());

  while (!loop.HasQuitted()) {

    if (MainScreen::exit == true) {
      std::cout << "TEST$WRTES" << endl;
      ExitScreen(screen);
    }
    loop.RunOnce();
  }

  int row = 0;

  return EXIT_SUCCESS;
}
