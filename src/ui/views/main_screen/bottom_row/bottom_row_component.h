
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace BottomRow {

Component BottomRowComponent();
Component TabMenuComponent();

Component TabContainerComponent();

std::string MenuTitle(int menu_index);
} // namespace BottomRow
