#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <i18ncpp.h>
#include <stdlib.h>
#include <string>

using namespace std;

namespace UIState {

// i18n object
inline i18n::I18N i18_object;

// Checked every loop, closes if set
inline bool Exit = false;

// Heading text, shows most recent log
inline string most_recent_log = UIState::i18_object.tr("sakura_init");

// Value for the selected menu on the main tab, saves tab is a different
// variable
inline int SelectedMenu = 0;

// Value for the selected menu on the saves tab
inline int SelectedSaveMenu = 0;

// Loads the ASCII art for the given menu (TODO: implement later)
void load_ascii();

// Hold the index of the current focus tab in the roms table
inline int SelectedRomTableIndex = 0;

// Hold the index of the current focus tab in the SRAM table
inline int SelectedSRAMTableIndex = 0;

// Hold the index of the current focus tab in the save states table
inline int SelectedSaveStateTableIndex = 0;

// Label strings for control ui buttons
inline string start_rom_label = "...";
inline string stop_rom_label = "...";
inline string open_rom_folder_label = "...";
inline string open_SRAM_folder_label = "...";
inline string save_state_label = "...";
inline string load_state_label = "...";
inline string start_label = "...";
inline string select_label = "...";
inline string a_label = "...";
inline string b_label = "...";
inline string up_label = "...";
inline string down_label = "...";
inline string left_label = "...";
inline string right_label = "...";

// Holds color options
inline ftxui::Color colors[] = {
    ftxui::Color::Black,   ftxui::Color::Blue,     ftxui::Color::Red,
    ftxui::Color::Green,   ftxui::Color::Cyan,     ftxui::Color::Pink1,
    ftxui::Color::Orange1, ftxui::Color::GrayDark, ftxui::Color::HotPink,
    ftxui::Color::White,

};

// Holds language local options
inline string locale_entries[2] = {"en", "jp"};

} // namespace UIState
