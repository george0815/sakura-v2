
#include "top_row_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

/* TODO: PADDING
 * SET COLOR
 * COMMENTS
 * GET VALUES FROM SETTINGS CONFIG / VARIABLES*/

using namespace ftxui;

Component TopRow::ControlsContainer() {

  return Container::Vertical({

      Renderer([&] {
        return text("Start rom: F3") | color(Color::Green) | borderEmpty;
      }),
      Renderer([&] {
        return text("Stop rom: F4") | color(Color::Green) | borderEmpty;
      }),
      Renderer([&] {
        return text("Open rom folder: F5") | color(Color::LightSkyBlue1) |
               borderEmpty;
      }),
      Renderer([&] {
        return text("Open SRAM folder: F6") | color(Color::Purple) |
               borderEmpty;
      }),
      Renderer([&] {
        return text("Save state: F7") | color(Color::Red) | borderEmpty;
      }),
      Renderer([&] {
        return text("Load state: F8") | color(Color::Orange1) | borderEmpty;
      }),
  });
}
