#include "controls_component.h"
#include "../../../../general/general_views.h"
#include <iostream>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;

//==========================
//
// This namespace is for the controls submenu and any logic that is associated
// with it.
//
// Current memebers: ControlsComponent
//
//==========================

namespace ControlsComponent {

// Returns controls menu component
Component ControlsComponent() {

  // Main container
  return Container::Vertical({

             GeneralViews::ControlOptionComponent("Start rom :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("Load rom :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("Open rom folder :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("Open SRAM folder :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("Save state :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("Load state :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("START :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("SELECT :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("A :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("B :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("UP :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("DOWN :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("LEFT :", 0),
             Renderer([&] { return text(""); }),
             GeneralViews::ControlOptionComponent("RIGHT :", 0),
             Renderer([&] { return text(""); }),
             Renderer([&] { return separator(); }),

             // Save button
             Button(
                 "Save", [&] { cout << "test"; }, ButtonOption::Ascii()),

         }) |
         borderEmpty;
}

} // namespace ControlsComponent
