#include "../main_screen.h"
#include "bottom_row_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

/* TODO: PADDING, COLOR
 * COMMENTS
 * GET VALUES FROM SETTINGS CONFIG / VARIABLES*/

using namespace ftxui;

ButtonOption Style() {
  auto option = ButtonOption::Ascii();
  return option;
};

std::vector<std::string> submenus = {"Roms", "Saves", "Settings", "Controls",
                                     "log"};

Component BottomRow::TabContainerComponent() {
  return Container::Tab(

      {

          Renderer([] { return text("sakura-v2") | borderEmpty; }),
          Renderer([] { return text("sakura-v2") | borderEmpty; }),

      },
      &MainScreen::selected_menu);
}

Component BottomRow::TabMenuComponent() {

  return Container::Vertical({
      Menu(&submenus, &MainScreen::selected_menu) |
          size(ftxui::WIDTH, ftxui::GREATER_THAN, 18) | flex,

      Button(
          " Exit ",
          [&] {
            MainScreen::exit = true;
            std::cout << MainScreen::exit << std::endl;
          },
          Style()) |
          center | size(ftxui::HEIGHT, ftxui::LESS_THAN, 3) | borderEmpty,

  });
}
