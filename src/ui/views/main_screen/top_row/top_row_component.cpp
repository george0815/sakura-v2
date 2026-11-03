
// this project
#include "top_row_component.h"
#include "../../../settings/settings.h"
#include "../../../views/general/general_views.h"

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

//==========================
//
// This namespace is for the top row component and any logic that is
// associated with them.
//
// Current memebers: TopRowComponent
//
//==========================

using namespace Settings;     // disable_ascii, disable_colored_hotkey_info
using namespace ftxui;        // Components and elements
using namespace GeneralViews; // Padding

namespace TopRow {

// returns component combining the top row
Component TopRowComponent() {
  return Container::Horizontal({

             // AsciiBox, renders if enabled
             (!disable_ascii ? AsciiBox() : Padding()),

             // If theres no ascii box, no padding since the InfoContainer will
             // be all the way to the left
             (!disable_ascii ? Padding(3) : Padding()), InfoContainer(),

             // Always renders
             Padding(7),

             // Control section, renders if enabled
             (!disable_colored_hotkey_info ? ControlsContainer() : Padding())

         }) |
         size(ftxui::HEIGHT, ftxui::LESS_THAN, 100); // Sets max size of top row
}

} // namespace TopRow
