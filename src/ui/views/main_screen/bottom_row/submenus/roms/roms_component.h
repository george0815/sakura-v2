#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;
using namespace std;

namespace RomsComponent {

// Returns rom submenu component
ftxui::Component RomTableComponent();

// Variable that holds rom component
inline Component RomSubmenuComponent;

// Starts rom (yes I know my comments are redundant but I just like commenting a
// lot)
void StartRom(int index);

} // namespace RomsComponent
