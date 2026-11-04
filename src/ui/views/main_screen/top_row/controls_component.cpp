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
using namespace UIState; // labels, I18nObject

// Shows the current controls for UI, (NES controls are in the controls
// submenu), each text is a combo of the translation string and the label for
// the controller button (as in, the button the user has to click to set a
// certain control)
Component TopRow::ControlsContainer() {

  return Container::Vertical({

      Renderer([&] {
        return text(I18nObject.tr("Start_rom:_") + StartRomLabel) |
               color(Color::Green) | borderEmpty;
      }),
      Renderer([&] {
        return text(I18nObject.tr("Stop_rom:_") + StopRomLabel) |
               color(Color::LightSkyBlue1) | borderEmpty;
      }),
      Renderer([&] {
        return text(I18nObject.tr("Open_rom_folder:_") + OpenRomFolderLabel) |
               color(Color::Purple) | borderEmpty;
      }),
      Renderer([&] {
        return text(I18nObject.tr("Open_SRAM_folder:_") + OpenSRAMFolderLabel) |
               color(Color::Pink1) | borderEmpty;
      }),
      Renderer([&] {
        return text(I18nObject.tr("Load_state:_") + SaveStateLabel) |
               color(Color::Red) | borderEmpty;
      }),
      Renderer([&] {
        return text(I18nObject.tr("Load_state:_") + LoadStateLabel) |
               color(Color::Orange1) | borderEmpty;
      }),
  });
}
