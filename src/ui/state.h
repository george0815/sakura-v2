#include <stdlib.h>
#include <string>

using namespace std;

namespace UIState {

// Checked every loop, closes if set
inline bool Exit = false;

// Value for the selected menu on the main tab, saves tab is a different
// variable
inline int SelectedMenu = 0;

// Value for the selected menu on the saves tab
inline int SelectedSaveMenu = 0;

// Loads the ASCII art for the given menu (TODO: implement later)
void load_ascii();

// Hold the index of the current focus tab in the roms table
inline int SelectedRomTableIndex = 0;

// Hold the index of the current focus tab in the roms table
inline int SelectedSRAMTableIndex = 0;

// Hold the index of the current focus tab in the roms table
inline int SelectedSaveStateTableIndex = 0;

inline string test_button_label = "TEST";

} // namespace UIState
