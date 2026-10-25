#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;
using namespace std;

namespace LogComponent {

// Uses GeneralViews::AddFocusableText to add a log Entry
void AddLogEntry(Component &comp, string str);

// Returns log component, basically just a Container::Vertical
Component LogComponent();

// Holds actual component returned from LogComponent()
inline Component LogSubmenuComponent;

} // namespace LogComponent
