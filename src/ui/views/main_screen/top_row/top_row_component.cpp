
#include "top_row_component.h"
#include "../../../settings/settings.h"

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

//==========================
//
// This namespace is for the top row component and any logic that is
// associated with them.
//
// Current memebers: TopRowComponent
//
//==========================

namespace TopRow {

Component TopRowComponent() {
  return Container::Horizontal({

             (!Settings::disable_ascii ? AsciiBox()
                                       : Renderer([] { return text(""); })),

             Renderer([] {
               return (!Settings::disable_ascii ? text("     ") : text(""));
             }), // Padding, TODO: Replace with general padding component
             InfoContainer(),

             Renderer([] { return text("            "); }),

             (!Settings::disable_colored_hotkey_info
                  ? ControlsContainer()
                  : Renderer([] { return text(""); }))}) |
         size(ftxui::HEIGHT, ftxui::LESS_THAN, 100); // Sets max size of top row
}

} // namespace TopRow
