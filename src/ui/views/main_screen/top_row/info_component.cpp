#include "top_row_component.h"
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

Component TopRow::InfoContainer() {

  return Container::Vertical({

      Renderer([&] { return text("sakura-v2") | borderEmpty; }),
      Renderer([&] { return text("Roms: 0") | borderEmpty; }),
  });
}
