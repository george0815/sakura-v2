#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;
using namespace std;

namespace LogComponent {

// Returns log component, basically just a Container::Vertical
Component LogComponent();

// Holds actual component returned from LogComponent(). I set it to nullptr
// because on startup savesettings and loadsettings are called before the UI is
// setup. So calling AddLogEntry would lead to a segfault. So I set it to
// nullptr, then check it in LoadSettings/SaveSettings so that I can still print
// messages to the log after the uses presses the save button, without it
// crashing at startup.
inline Component LogSubmenuComponent = nullptr;

// Uses GeneralViews::AddFocusableText to add a log Entry
void AddLogEntry(string str = "");

} // namespace LogComponent
