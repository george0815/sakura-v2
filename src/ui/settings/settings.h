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
inline int StartRomControl = 0x4000003au;
inline int StopRomControl = 0x4000003bu;
inline int OpenRomFolderControl = 0x4000003cu;
inline int OpenSRAMFolderControl = 0x4000003du;
inline int SaveStateControl = 0x4000003eu;
inline int LoadStateControl = 0x4000003fu;
inline int StartControl = 0x0000000du;
inline int SelectControl = 0x00000008u;
inline int AControl = (int)'a';
inline int BControl = (int)'z';
inline int UpControl = 0x40000052u;
inline int DownControl = 0x40000051u;
inline int LeftControl = 0x40000050u;
inline int RightControl = 0x4000004fu;

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
