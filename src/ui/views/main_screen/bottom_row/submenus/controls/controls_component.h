

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;
using namespace std;

namespace ControlsComponent {

// Returns controls menu component
Component ControlsComponent();

// Variable that holds controls component
inline Component ControlsSubmenuComponent = ControlsComponent();

// Convert ftxui key code -> SDL2
int KeyCodeToSDL3(const Event &key_event);

// Convert SDL3 key code -> ftxui
string KeyCodeToFTXUI(int code);

} // namespace ControlsComponent
