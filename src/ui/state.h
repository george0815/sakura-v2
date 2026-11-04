#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <i18ncpp.h>
#include <stdlib.h>
#include <string>

using namespace std;

namespace UIState {

// i18n object
inline i18n::I18N I18nObject;

// Checked every loop, closes if set
inline bool Exit = false;

// Heading text, shows most recent log
inline string MostRecentLog = I18nObject.tr("sakura_init");

// Value for the selected menu on the main tab, saves tab is a different
// variable
inline int SelectedMenu = 0;

// Value for the selected menu on the saves tab
inline int SelectedSaveMenu = 0;

// Hold the index of the current focus tab in the roms table
inline int SelectedRomTableIndex = 0;

// Hold the index of the current focus tab in the SRAM table
inline int SelectedSRAMTableIndex = 0;

// Hold the index of the current focus tab in the save states table
inline int SelectedSaveStateTableIndex = 0;

// Label strings for control ui buttons
inline string StartRomLabel = "...";
inline string StopRomLabel = "...";
inline string OpenRomFolderLabel = "...";
inline string OpenSRAMFolderLabel = "...";
inline string SaveStateLabel = "...";
inline string LoadStateLabel = "...";
inline string StartLabel = "...";
inline string SelectLabel = "...";
inline string ALabel = "...";
inline string BLabel = "...";
inline string UpLabel = "...";
inline string DownLabel = "...";
inline string LeftLabel = "...";
inline string RightLabel = "...";

// Holds color options
inline ftxui::Color ColorEntries[] = {
    ftxui::Color::Black,   ftxui::Color::Blue,     ftxui::Color::Red,
    ftxui::Color::Green,   ftxui::Color::Cyan,     ftxui::Color::Pink1,
    ftxui::Color::Orange1, ftxui::Color::GrayDark, ftxui::Color::HotPink,
    ftxui::Color::White,

};

// Holds language local options
inline string LocaleEntries[2] = {"en", "jp"};

// Used by the general control button component to know whether the button is
// waiting for input
inline bool WaitingForInput = false;

} // namespace UIState
