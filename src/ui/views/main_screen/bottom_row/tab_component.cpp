
#include "bottom_row_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

/* TODO: PADDING, COLOR
 * COMMENTS
 * GET VALUES FROM SETTINGS CONFIG / VARIABLES*/

using namespace ftxui;

std::vector<std::string> submenus = {"Roms", "Saves", "Settings", "Controls",
                                     "log"};

int selected_menu = 0;
auto tab_menu = Menu(&submenus, &selected_menu);

auto submenu_container = Container::Tab(

    {

        Renderer([] { return text("sakura-v2") | borderEmpty; }),
        Renderer([] { return text("sakura-v2") | borderEmpty; }),

    },
    &selected_menu);

auto container = Container::Horizontal({tab_menu | border, submenu_container

});

Component BottomRow::TabContainerComponent() { return container; }

Component BottomRow::TabMenuComponent() {

  return Container::Vertical({

      Renderer([&] { return text("sakura-v2") | borderEmpty; }),
      Renderer([&] { return text("Roms: 0") | borderEmpty; }),
  });
}
