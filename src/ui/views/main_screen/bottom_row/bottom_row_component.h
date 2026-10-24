
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace BottomRow {

// Returns bottoms row component
Component BottomRowComponent();

// Returns tab components, implementations in tab_component.cpp
Component TabMenuComponent();
Component TabContainerComponent();

} // namespace BottomRow
