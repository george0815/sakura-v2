#include "settings.h"
#include "../state.h"
#include "../views/main_screen/bottom_row/submenus/controls/controls_component.h"
#include "../views/main_screen/bottom_row/submenus/log/log_component.h"
#include <filesystem>
#include <fstream>
#include <ftxui/dom/direction.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

using namespace nlohmann;
using namespace std;
using namespace filesystem;

//==========================
//
// This namespace is for the settings and any logic that is associated
// with it.
//
// Current members: all the variables that hold the actual settings values (in
// header file), SaveSettings, LoadSettings, VerifyFolder, VerifyFile,
// OpenFolder
//
//==========================

// TODO::  1. Add other settings
// 2. Add open folder function
//

using namespace std;
using namespace UIState; // I18nObject, control button labels

namespace Settings {

// Opens a given folder
int OpenFolder(string folder, string &error_message) {

  // For windows (TODO: add windows support)

  // For linux,
  string tmp = "xdg-open " + folder + " >nul 2>nul";
  if (system(tmp.c_str()) != 0) {
    error_message = I18nObject.tr("Failed_to_open_folder");
    return -1;
  }

  return 0;
}

// Serializes settings namespace to JSON
int SaveSettings(bool backup) {

  // Declare json object
  json settings_json;

  // Set values in json object

  // Bool values
  settings_json["EnableDetailedLogging"] = EnableDetailedLogging;
  settings_json["DisableColoredHotkeyInfo"] = DisableColoredHotkeyInfo;
  settings_json["DisableASCII"] = DisableASCII;

  // Inputs
  settings_json["DefaultRomPath"] = DefaultRomPath;
  settings_json["RomsPaths"] = RomsPaths;
  settings_json["LogPath"] = LogPath;
  settings_json["SRAMPath"] = SRAMPath;
  settings_json["SaveStatePath"] = SaveStatePath;

  // Color and language
  settings_json["BackgroundColor"] = BackgroundColor;
  settings_json["TextAndBorderColor"] = TextAndBorderColor;
  settings_json["ASCIIColor"] = ASCIIColor;
  settings_json["language"] = Language;

  // Controls
  settings_json["StartRomControl"] = StartRomControl;
  settings_json["StopRomControl"] = StopRomControl;
  settings_json["OpenRomFolderControl"] = OpenRomFolderControl;
  settings_json["OpenSRAMFolderControl"] = OpenSRAMFolderControl;
  settings_json["SaveStateControl"] = SaveStateControl;
  settings_json["LoadStateControl"] = LoadStateControl;
  settings_json["StartControl"] = StartControl;
  settings_json["SelectControl"] = SelectControl;
  settings_json["AControl"] = AControl;
  settings_json["BControl"] = BControl;
  settings_json["UpControl"] = UpControl;
  settings_json["DownControl"] = DownControl;
  settings_json["LeftControl"] = LeftControl;
  settings_json["RightControl"] = RightControl;

  // Create and write to file, either main or create a backup
  string tmp_config_filename = backup ? "config_backup.ini" : "config.ini";
  ofstream config_stream(tmp_config_filename);
  config_stream << settings_json;
  config_stream.close();

  return 0;
}

// Serializes settings namespace to JSON
int LoadSettings(bool backup) {

  // Create json object as object, has to be set to json::object or else it will
  // be treated as a string
  json settings_json = json::object();

  string tmp_config_filename = backup ? "config_backup.ini" : "config.ini";
  ifstream config_stream(tmp_config_filename);

  // Read to buffer
  stringstream buffer;
  buffer << config_stream.rdbuf();

  // Try loading
  try {

    // Set Settings namespace values
    settings_json = json::parse(buffer.str());

    // Bool values
    EnableDetailedLogging = settings_json["EnableDetailedLogging"].get<bool>();
    DisableColoredHotkeyInfo =
        settings_json["DisableColoredHotkeyInfo"].get<bool>();
    DisableASCII = settings_json["DisableASCII"].get<bool>();

    // Inputs
    DefaultRomPath = settings_json["DefaultRomPath"];
    RomsPaths = settings_json["RomsPaths"];
    LogPath = settings_json["LogPath"];
    SRAMPath = settings_json["SRAMPath"];
    SaveStatePath = settings_json["SaveStatePath"];

    // Color and language
    BackgroundColor = settings_json["BackgroundColor"];
    TextAndBorderColor = settings_json["TextAndBorderColor"];
    ASCIIColor = settings_json["ASCIIColor"];
    Language = settings_json["language"];

    // Controls
    StartRomControl = settings_json["StartRomControl"];
    StopRomControl = settings_json["StopRomControl"];
    OpenRomFolderControl = settings_json["OpenRomFolderControl"];
    OpenSRAMFolderControl = settings_json["OpenSRAMFolderControl"];
    SaveStateControl = settings_json["SaveStateControl"];
    LoadStateControl = settings_json["LoadStateControl"];
    StartControl = settings_json["StartControl"];
    SelectControl = settings_json["SelectControl"];
    AControl = settings_json["AControl"];
    BControl = settings_json["BControl"];
    UpControl = settings_json["UpControl"];
    DownControl = settings_json["DownControl"];
    LeftControl = settings_json["LeftControl"];
    RightControl = settings_json["RightControl"];

    // Set control labels
    StartRomLabel = ControlsComponent::KeyCodeToFTXUI(StartRomControl);
    StopRomLabel = ControlsComponent::KeyCodeToFTXUI(StopRomControl);
    OpenRomFolderLabel =
        ControlsComponent::KeyCodeToFTXUI(OpenRomFolderControl);
    OpenSRAMFolderLabel =
        ControlsComponent::KeyCodeToFTXUI(OpenSRAMFolderControl);
    SaveStateLabel = ControlsComponent::KeyCodeToFTXUI(SaveStateControl);
    LoadStateLabel = ControlsComponent::KeyCodeToFTXUI(LoadStateControl);
    StartLabel = ControlsComponent::KeyCodeToFTXUI(StartControl);
    SelectLabel = ControlsComponent::KeyCodeToFTXUI(SelectControl);
    ALabel = ControlsComponent::KeyCodeToFTXUI(AControl);
    BLabel = ControlsComponent::KeyCodeToFTXUI(BControl);
    UpLabel = ControlsComponent::KeyCodeToFTXUI(UpControl);
    DownLabel = ControlsComponent::KeyCodeToFTXUI(DownControl);
    LeftLabel = ControlsComponent::KeyCodeToFTXUI(LeftControl);
    RightLabel = ControlsComponent::KeyCodeToFTXUI(RightControl);

  }
  // There's a shitton of exceptions that can be thrown here so I'm catching all
  catch (...) {
    LogComponent::AddLogEntry(I18nObject.tr("Error_loading_settings:_"));
    config_stream.close();
    return -1;
  }
  config_stream.close();
  return 0;
}

// Verifies if a given string is 1. A proper directory, 2. Exists, and 3. Can be
// written to/read from
int VerifyFolder(string directory, string &error_message) {

  // Either not a folder or doesn't exist in the first place
  path tmp_dir = directory;
  if (!exists(tmp_dir) || !is_directory(tmp_dir)) {
    error_message = I18nObject.tr("Error") + ": " + tmp_dir.string() + " " +
                    I18nObject.tr("does_not_exist_folder");
    return -1;
  }

  // Can read from?
  bool can_read = true;
  try {
    directory_iterator it(tmp_dir);
    can_read = true;
  } catch (const filesystem_error) {
    can_read = false;
    error_message = I18nObject.tr("Error") + ": " +
                    I18nObject.tr("cannot_read_from") + tmp_dir.string();
  }

  // Can write to?
  bool can_write = true;
  try {
    // Create tmp file in directory and attempt to write to it
    path tmp_file = tmp_dir / "permissions_check.tmp";
    ofstream tmp_stream(tmp_file);
    tmp_stream.close();
    remove("permissions_check.tmp");
  } catch (filesystem_error) {
    can_write = false;
    error_message = I18nObject.tr("Error") + ": " +
                    I18nObject.tr("cannot_write_to") + tmp_dir.string();
  }

  if (!can_read || !can_write) {
    return -1;
  }

  return 0;
}

// Verifies if a given string is 1. A proper file, 2. Exists, and 3. Can be
// read from
int VerifyFile(string file, string &error_message) {

  // Either not a folder or doesn't exist in the first place
  path tmp_dir = file;
  if (!exists(tmp_dir) || !is_regular_file(tmp_dir)) {
    error_message = I18nObject.tr("Error") + ": " + tmp_dir.string() +
                    I18nObject.tr("does_not_exist_file");
    return -1;
  }

  // Can read from?
  bool can_read = true;
  ifstream tmp_file(tmp_dir);
  if (!tmp_file) {
    can_read = false;
  } else {
    can_read = true;
  }

  if (!can_read) {
    error_message = I18nObject.tr("Error") + ": " +
                    I18nObject.tr("cannot_read") + tmp_dir.string();
    return -1;
  }

  return 0;
}

} // namespace Settings
