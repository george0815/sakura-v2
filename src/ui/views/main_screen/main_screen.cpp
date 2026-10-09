
#include "main_screen.h"
#include "bottom_row/bottom_row_component.h"
#include "top_row/top_row_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>

Component MainScreen::MainScreenComponent() {

  return Container::Vertical(

      {TopRow::TopRowComponent(), BottomRow::BottomRowComponent() | flex}

  );
}
