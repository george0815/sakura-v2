

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

namespace SavesComponent {

// Returns saves menu components
Component SavesComponent();
Component SavesTabContainerComponent();
Component SavesTabMenuComponent();

// Variable that holds saves menu component
inline Component SavesSubmenuComponent = SavesComponent();

} // namespace SavesComponent
