#include "top_row_component.h"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

Component TopRow::AsciiBox() {

  return Renderer([&] {
    auto c = Canvas(100, 100);
    c.DrawText(0, 0, "A block filled with text");
    return canvas(std::move(c)) | border;
  });
}
