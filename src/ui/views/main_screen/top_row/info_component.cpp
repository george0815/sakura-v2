#include "../../../settings/settings.h"
#include "../../../state.h"
#include "../bottom_row/submenus/roms/roms_component.h"
#include "top_row_component.h"

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;
using namespace RomsComponent; // RomList
using namespace UIState;       // I18nObject

// Just contains info text, name of the program
Component TopRow::InfoContainer() {

  // If both elements are the header, collapse and display Horizontally
  if (Settings::DisableASCII && Settings::DisableColoredHotkeyInfo) {

    return Container::Horizontal({

        Renderer([&] { return text("sakura-v2") | borderEmpty; }),
        Renderer([&] {
          return text(I18nObject.tr("Roms:_") + to_string(RomList.size())) |
                 borderEmpty;
        }),
    });
  }

  // Else, display vertically
  return Container::Vertical({

      Renderer([&] { return text("sakura-v2") | borderEmpty; }),
      Renderer([&] {
        return text(I18nObject.tr("Roms:_") + to_string(RomList.size())) |
               borderEmpty;
      }),

  });
}
