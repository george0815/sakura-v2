#include <nlohmann/json.hpp>

using namespace std;

namespace Settings {

//=======================
// ACTUAL SETTINGS
//=======================

// Bool values
inline bool DisableColoredHotkeyInfo = false;
inline bool EnableDetailedLogging = false;
inline bool DisableASCII = false;

// Inputs
inline string DefaultRomPath = "roms/";
inline string RomsPaths = "";
inline string LogPath = "log.txt";
inline string SRAMPath = "saves/SRAM/";
inline string SaveStatePath = "saves/save_states/";

// Color options and
// language
inline int BackgroundColor = 0;
inline int TextAndBorderColor = 9;
inline int ASCIIColor = 5;
inline int Language = 1;

// Controls
inline int StartRomControl = 0;
inline int StopRomControl = 0;
inline int OpenRomFolderControl = 0;
inline int OpenSRAMFolderControl = 0;
inline int SaveStateControl = 0;
inline int LoadStateControl = 0;
inline int StartControl = 0;
inline int SelectControl = 0;
inline int AControl = 0;
inline int BControl = 0;
inline int UpControl = 0;
inline int DownControl = 0;
inline int LeftControl = 0;
inline int RightControl = 0;

//=======================
// SAVING AND LOADING
//=======================

// Serializes the namepsace to JSON
int SaveSettings(bool backup);

// Deerializes, maps values from JSON to the namepsace
int LoadSettings(bool backup);

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
