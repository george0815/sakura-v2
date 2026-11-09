

#include "bottom_row_component.h"
#include "../../../state.h"
#include "../main_screen.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

//==========================
//
// This namespace is for the bottom row and any logic that is associated
// with it.
//
// Current members: BottomRowComponent
//
//==========================

// Component composing of the entire bottom row,
Component BottomRow::BottomRowComponent() {

  return Container::Horizontal({

             // Tab component showing options
             TabMenuComponent() | border,

             // Container::Vertical, section showning the most recent log on
             // top, right now just has placeholder data
             Container::Vertical({Renderer([&] {
                                    // Most recent log
                                    return text(UIState::MostRecentLog);
                                  }) | border,

                                  // Main tab contents
                                  TabContainerComponent() | flex | border}) |
                 flex,

         }) |
         flex;
}
