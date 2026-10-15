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
inline string roms_paths = "";
inline string default_rom_path = "";
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
inline int load_rom_control = 0;
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
int save_settings();

// Deerializes, maps values from JSON to the namepsace
int load_settings();

//=======================
// VERIFICATION
//=======================

// Verify's if the path to a given file is valid
int verify_file(string path);

// Verify's if the path to a given folder is valid
int verify_folder(string path);

}; // namespace Settings
