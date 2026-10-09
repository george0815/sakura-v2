

#include "bottom_row_component.h"
#include "../main_screen.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

Component BottomRow::BottomRowComponent() {
  return Container::Horizontal({
      TabMenuComponent() | border,

      Renderer([&] {
        return ftxui::window(text(MenuTitle(MainScreen::selected_menu)),
                             TabContainerComponent()->Render());
      }) | flex,

  });
}

std::string BottomRow::MenuTitle(int menu_index) {

  switch (menu_index) {

  case (0):
    return "Roms";
  case (1):
    return "Saves";
  case (2):
    return "Settings";
  case (3):
    return "Controls";
  case (4):
    return "Log";
  }
  return "Roms";
}
