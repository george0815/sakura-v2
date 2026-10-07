

#include "top_row_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

Component TopRow::TopRowComponent() {
  return Container::Horizontal(
      {AsciiBox(), InfoContainer(), ControlsContainer()});
}
