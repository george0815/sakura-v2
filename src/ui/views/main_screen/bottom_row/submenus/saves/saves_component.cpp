

#include "saves_component.h"
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
// This namespace is for the saves submenu and any logic that is associated
// with it.
//
// Current memebers: SavesComponent
//
//==========================

namespace SavesComponent {

// Returns controls menu component
Component SavesComponent() {

  // Main container
  return Container::Vertical({

  });
}

} // namespace SavesComponent
