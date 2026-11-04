#include "settings.h"
#include "../state.h"
#include "../views/main_screen/bottom_row/submenus/controls/controls_component.h"
#include "../views/main_screen/bottom_row/submenus/log/log_component.h"
#include <filesystem>
#include <fstream>
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

namespace Settings {

// Opens a given folder
int OpenFolder(string folder, string &error_message) {

  // For windows (TODO: add windows support)

  // For linux,
  string tmp = "xdg-open " + folder + " >nul 2>nul";
  if (system(tmp.c_str()) != 0) {
    error_message = "Failed to open folder."; // TODO: add this string to the
                                              // i18n resource files
  }

  return 0;
}

// Serializes settings namespace to JSON
int SaveSettings(bool backup) {

  // Declare json object
  json settings_json;

  // Set values in json object

  // Bool values
  settings_json["enable_detailed_logging"] = Settings::EnableDetailedLogging;
  settings_json["disable_colored_hotkey_info"] =
      Settings::DisableColoredHotkeyInfo;
  settings_json["disable_ascii"] = Settings::DisableASCII;

  // Inputs
  settings_json["default_rom_path"] = Settings::DefaultRomPath;
  settings_json["roms_paths"] = Settings::RomsPaths;
  settings_json["log_path"] = Settings::LogPath;
  settings_json["sram_path"] = Settings::SRAMPath;
  settings_json["save_state_path"] = Settings::SaveStatePath;

  // Color and language
  settings_json["background_color"] = Settings::BackgroundColor;
  settings_json["text_and_border_color"] = Settings::TextAndBorderColor;
  settings_json["ascii_color"] = Settings::ASCIIColor;
  settings_json["language"] = Settings::Language;

  // Controls
  settings_json["start_rom_control"] = Settings::StartRomControl;

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
    Settings::EnableDetailedLogging =
        settings_json["enable_detailed_logging"].get<bool>();
    Settings::DisableColoredHotkeyInfo =
        settings_json["disable_colored_hotkey_info"].get<bool>();
    Settings::DisableASCII = settings_json["disable_ascii"].get<bool>();

    // Inputs
    Settings::DefaultRomPath = settings_json["default_rom_path"];
    Settings::RomsPaths = settings_json["roms_paths"];
    Settings::LogPath = settings_json["log_path"];
    Settings::SRAMPath = settings_json["sram_path"];
    Settings::SaveStatePath = settings_json["save_state_path"];

    // Color and language
    Settings::BackgroundColor = settings_json["background_color"];
    Settings::TextAndBorderColor = settings_json["text_and_border_color"];
    Settings::ASCIIColor = settings_json["ascii_color"];
    Settings::Language = settings_json["language"];

    // Controls
    Settings::StartRomControl = settings_json["start_rom_control"];

    // Set control labels
    UIState::StartRomLabel =
        ControlsComponent::KeyCodeToFTXUI(Settings::StartRomControl);

  }
  // There's a shitton of exceptions that can be thrown here so I'm catching all
  catch (...) {
    LogComponent::AddLogEntry(
        "Error loading settings."); // TODO:: change to i18n string
    config_stream.close();
    return -1;
  }
  config_stream.close();
  return 0;
}

// Verifies if a given string is 1. A proper directory, 2. Exists, and 3. Can be
// written to/read from
// TODO: Set error message
int VerifyFolder(string directory, string &error_message) {

  // Either not a folder or doesn't exist in the first place
  path tmp_dir = directory;
  if (!exists(tmp_dir) || !is_directory(tmp_dir)) {
    error_message = UIState::I18nObject.tr("Error") + ": " + tmp_dir.string() +
                    " " + UIState::I18nObject.tr("does_not_exist_folder");
    return -1;
  }

  // Can read from?
  bool can_read = true;
  try {
    directory_iterator it(tmp_dir);
    can_read = true;
  } catch (const filesystem_error) {
    can_read = false;
    error_message = UIState::I18nObject.tr("Error") + ": " +
                    UIState::I18nObject.tr("cannot_read_from") +
                    tmp_dir.string();
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
    error_message = UIState::I18nObject.tr("Error") + ": " +
                    UIState::I18nObject.tr("cannot_write_to") +
                    tmp_dir.string();
  }

  if (!can_read || !can_write) {
    return -1;
  }

  return 0;
}

// Verifies if a given string is 1. A proper file, 2. Exists, and 3. Can be
// read from
// TODO: Set error message
int VerifyFile(string file, string &error_message) {

  // Either not a folder or doesn't exist in the first place
  path tmp_dir = file;
  if (!exists(tmp_dir) || !is_regular_file(tmp_dir)) {
    error_message = UIState::I18nObject.tr("Error") + ": " + tmp_dir.string() +
                    UIState::I18nObject.tr("does_not_exist_file");
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
    error_message = UIState::I18nObject.tr("Error") + ": " +
                    UIState::I18nObject.tr("cannot_read") + tmp_dir.string();
    return -1;
  }

  return 0;
}

} // namespace Settings
