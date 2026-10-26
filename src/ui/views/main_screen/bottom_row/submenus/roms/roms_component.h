#include <cstdint>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>

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

// Calls LoadRomFolder on multiple directories to update roms list
void LoadAllRoms();

// Loads roms from single directory
void LoadRomFolder(string directory);

// Rom struct, containing various information about a given rom. Different from
// the Cart struct in the core
struct Rom {

  string name;
  string path;
  uintmax_t size;
};

// List of rom structs
inline vector<Rom> RomList;

} // namespace RomsComponent
