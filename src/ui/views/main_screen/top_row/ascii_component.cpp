#include "top_row_component.h"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

/**
 * TODO: SET DIMENSIONS
 * TEXT COLOR
 * SET ASCII
 * COMMENTS
 *
 */

using namespace ftxui;

Component TopRow::AsciiBox() {

  return Renderer([&] {
    auto c = Canvas(130, 100);

    c.DrawText(0, 0, "         ⠀⠀⠀⠀        ⠀⠀⠀⠀⠀⠀⢀⣴⣿⣦⣀⢀⣴⣿⣦  ⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⠀   ",
               Color::Orange1);
    c.DrawText(0, 4, "     ⠀⠀          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀   ⠀",
               Color::Orange1);
    c.DrawText(0, 8, " ⠀ ⠀ ⠀⠀⠀⠀                ⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⠀   ",
               Color::Orange1);
    c.DrawText(0, 12, "    ⠀⠀⠀⠀                 ⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ",
               Color::Orange1);
    c.DrawText(0, 16, "               ⢀⣤⣴⣶⣿⣿⣿⣿⣿⣷⡈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢁⣾⣿⣿⣿⣿⣿⣶⣦⣤⡀⠀⠀  ",
               Color::Orange1);
    c.DrawText(0, 20, "  ⠀             ⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠙⣿⣿⣿⠛⠛⣿⣿⣿⠋⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀  ",
               Color::Orange1);
    c.DrawText(0, 24, "             ⠀ ⣀⣬⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡈⢻⣿⡄⢠⣿⡟⢁⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣥⣀    ",
               Color::Orange1);
    c.DrawText(0, 28, "              ⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⢿⣄⠹⣇⢸⠏⣠⡾⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀  ",
               Color::Orange1);
    c.DrawText(0, 32, "              ⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⣠⣌⣉⠁⠀⠀⠐⣉⣠⣄⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠀⠀  ",
               Color::Orange1);
    c.DrawText(0, 36, "               ⠀⠈⠻⣿⣿⣿⣿⣿⣿⡿⠿⠛⠋⣉⣠⠄⠀⠀⠠⣄⣉⠙⠛⠿⢿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀  ",
               Color::Orange1);
    c.DrawText(0, 40, "                 ⠀⠀⠙⠛⢉⣁⣤⣴⣶⣾⣿⠛⠃⣴⡟⢸⣦⠘⠛⣿⣿⣶⣦⣤⣈⡉⠛⠋⠁⠀⠀⠀⠀   ",
               Color::Orange1);
    c.DrawText(0, 44, "      ⠀            ⠀⣴⣿⣿⣿⣿⣿⣿⣿⣄⣤⣿⡇⢸⣿⣤⣠⣾⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀   ",
               Color::Orange1);
    c.DrawText(0, 48, "                  ⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀   ",
               Color::Orange1);
    c.DrawText(0, 52, "                  ⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀ ⠀ ⠀⠀",
               Color::Orange1);
    c.DrawText(0, 56, "                  ⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀ ⠀ ⠀⠀",
               Color::Orange1);
    c.DrawText(0, 60, "                   ⠹⠿⠛⠛⣿⣿⣿⣿⣿⣿⣿⠟⠁⠈⠻⣿⣿⣿⣿⣿⣿⣿⠛⠛⠿⠟⠀⠀⠀ ⠀ ⠀⠀",
               Color::Orange1);
    c.DrawText(0, 64, "  ⠀⠀                 ⠀⠀⢻⣿⣿⠿⠟⠋⠁⠀⠀⠀⠀⠈⠙⠻⠿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀  ⠀⠀⠀",
               Color::Orange1);
    c.DrawText(0, 68, "  ⠀⠀                  ⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀    ⠀",
               Color::Orange1);

    return canvas(std::move(c)) | border |
           size(ftxui::HEIGHT, ftxui::LESS_THAN, 18) |
           size(ftxui::WIDTH, ftxui::GREATER_THAN, 50);
  });
}
