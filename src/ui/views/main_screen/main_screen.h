
#include "bottom_row/bottom_row_component.h"
#include "top_row/top_row_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace MainScreen {

Component MainScreenComponent();
static int selected_menu = 0;
static bool exit = false;

}; // namespace MainScreen
