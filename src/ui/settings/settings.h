#include <nlohmann/json.hpp>

using namespace std;

namespace Settings {

//=======================
// ACTUAL SETTINGS
//=======================

// Bool values
inline bool disable_colored_hotkey_info = false;
inline bool enable_detailed_logging = false;
inline bool disable_ascii = false;

// Inputs
inline string default_rom_path = "/home/Hunter/Downloads/roms/";
inline string roms_paths;
inline string log_path = "";
inline string sram_path = "";
inline string save_state_path = "";

// Color options (will have find out what actual type ftxui::color is) and
// language
inline int background_color = 0;
inline int text_color = 0;
inline int focus_background_color = 0;
inline int focus_text_color = 0;
inline int ascii_color = 0;
inline int language = 0;

// Controls (will be ints for now but will probably be some SDL keycode or
// something later)
inline int start_rom_control = 0;
inline int stop_rom_control = 0;
inline int open_rom_folder_control = 0;
inline int open_sram_folder_control = 0;
inline int save_state_control = 0;
inline int load_state_control = 0;
inline int start_control = 0;
inline int select_control = 0;
inline int a_control = 0;
inline int b_control = 0;
inline int up_control = 0;
inline int down_control = 0;
inline int left_control = 0;
inline int right_control = 0;

//=======================
// SAVING AND LOADING
//=======================

// Serializes the namepsace to JSON
int save_settings(bool backup);

// Deerializes, maps values from JSON to the namepsace
int load_settings(bool backup);

//=======================
// VERIFICATION
//=======================

// Verify's if the path to a given file is valid
int VerifyFile(string path, string &error_message);

// Verfies if a folder 1. exists, 2. Can be read from/written to: returns 0 if
// OK
int VerifyFolder(string directory, string &error_message);

//=======================
// FUNCTIONALITY
//=======================

int OpenFolder(string folder, string &error_message);

}; // namespace Settings
