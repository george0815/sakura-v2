// this project
#include "../../../state.h"
#include "top_row_component.h"

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;   // ftxui components and elements
using namespace UIState; // labels, i18n_object

// Shows the current controls for UI, (NES controls are in the controls
// submenu), each text is a combo of the translation string and the label for
// the controller button (as in, the button the user has to click to set a
// certain control)
Component TopRow::ControlsContainer() {

  return Container::Vertical({

      Renderer([&] {
        return text(i18n_object.tr("Start_rom:_") + start_rom_label) |
               color(Color::Green) | borderEmpty;
      }),
      Renderer([&] {
        return text(i18n_object.tr("Stop_rom:_") + stop_rom_label) |
               color(Color::LightSkyBlue1) | borderEmpty;
      }),
      Renderer([&] {
        return text(i18n_object.tr("Open_rom_folder:_") +
                    open_rom_folder_label) |
               color(Color::Purple) | borderEmpty;
      }),
      Renderer([&] {
        return text(i18n_object.tr("Open_SRAM_folder:_") +
                    open_SRAM_folder_label) |
               color(Color::Pink1) | borderEmpty;
      }),
      Renderer([&] {
        return text(i18n_object.tr("Load_state:_") + save_state_label) |
               color(Color::Red) | borderEmpty;
      }),
      Renderer([&] {
        return text(i18n_object.tr("Load_state:_") + load_state_label) |
               color(Color::Orange1) | borderEmpty;
      }),
  });
}
