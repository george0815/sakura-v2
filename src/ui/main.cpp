#include "../core/CPU/CPU.h"
#include "views/main_screen/top_row/top_row_component.h"
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
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

ButtonOption Style() {
  auto option = ButtonOption::Animated();
  return option;
};

// stub for parseRom function
void parseRom(string &value) {
  value = "CHANGED";
  cout << "Parsing rom...";
}

void ExitScreen(ScreenInteractive &screen) { screen.Exit(); }

int main() {

  CPU *cpu = new CPU();

  ScreenInteractive screen = ScreenInteractive::TerminalOutput();
  string value = "not changed";

  auto parseRomButton = Button("Parse rom", [&] { parseRom(value); }, Style());
  auto exitButton = Button("Exit", [&] { ExitScreen(screen); }, Style());

  int row = 0;
  auto tmpContainer = Container::Vertical(
      {Container::Horizontal({parseRomButton, exitButton}, &row) | flex});
  /*
    auto component = Renderer(tmpContainer, [&] {
      return vbox({
          text("sakura-v2"),
          separator(),
          vbox({

              // FOR ROM DATA
              text("ROM DATA"),
              separator(),
              text("Constant: " +
                   std::to_string(cpu->S)), // should be "NES" in ASCII
              text("PRG_ROM_SiZE: " + std::to_string(cpu->P)),
              text("CHR: " + std::to_string(cpu->Y)),
              text("FLAGS_6: " + std::to_string(cpu->A)),
              text("FLAGS_7: " + std::to_string(cpu->A)),
              text("FLAGS_8: " + std::to_string(cpu->A)),
              text("FLAGS_0: " + std::to_string(cpu->A)),
              text("FLAGS_10: " + std::to_string(cpu->A)),

              // FOR CPU STATE
              separator(),
              text("CPU STATE"),
              separator(),
              text("PC: " + std::to_string(cpu->PC)),
              text("S: " + std::to_string(cpu->S)),
              text("Y: " + std::to_string(cpu->P)),
              text("Y: " + std::to_string(cpu->Y)),
              text("X: " + std::to_string(cpu->X)),
              text("A: " + std::to_string(cpu->A)),

              // FOR OPCODES
              vbox({
                  separator(),
                  text("INSTRUCTIONS"),
                  separator(),
              }),

          }),
          tmpContainer->Render() | flex,
      });
    });
  */

  screen.Loop(TopRow::TopRowComponent());

  return EXIT_SUCCESS;
}
