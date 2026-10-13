

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

namespace SettingsComponent {

// Returns controls menu component
Component SettingsComponent();

// Variable that holds controls component
inline Component SettingsSubmenuComponent = SettingsComponent();

} // namespace SettingsComponent
