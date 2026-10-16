
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;
using namespace std;

namespace SaveSubmenuComponent {

// Returns rom submenu component
ftxui::Component SaveSRAMTableComponent();
ftxui::Component SaveStateTableComponent();

// Variable that holds rom component
inline Component SRAMTable = SaveSRAMTableComponent();
inline Component SaveStatesTable = SaveStateTableComponent();

} // namespace SaveSubmenuComponent
