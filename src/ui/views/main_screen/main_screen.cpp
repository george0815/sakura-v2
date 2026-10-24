
#include "main_screen.h"
#include "bottom_row/bottom_row_component.h"
#include "top_row/top_row_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>

//==========================
//
// This namespace is for the main screen and any logic that is associated
// with it.
//
// Current memebers: MainScreenComponent
//
//==========================

Component MainScreen::MainScreenComponent() {

  // Just combines the top and bottom row
  return Container::Vertical(

      {TopRow::TopRowComponent(), BottomRow::BottomRowComponent() | flex}

  );
}
