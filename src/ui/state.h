

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

} // namespace UIState
