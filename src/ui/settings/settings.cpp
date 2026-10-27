#include "settings.h"
#include "../state.h"
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
// Current memebers: all the variables that hold the actual settings values (in
// header file), save_settings, load_settings)
//
//==========================

// TODO::  1. Add other settings
//         2. Add verification, handle edge cases on load (verification on save
//         will be handled in the save function)
//
//         TODO: Change error message to i18n strings

namespace Settings {

// Serializes settings namespace to JSON
int save_settings(bool backup) {

  // Declare json object
  json settings_json;

  // Set values in json object
  settings_json["enable_detailed_logging"] = Settings::enable_detailed_logging;
  settings_json["language"] = Settings::language;

  // Create and write to file, either main or create a backup
  string tmp_config_filename = backup ? "config.ini" : "config_backup.ini";
  ofstream config_stream(tmp_config_filename);
  config_stream << settings_json;
  config_stream.close();

  return 0;
}

// Serializes settings namespace to JSON
int load_settings(bool backup) {

  // Create json object as object, has to be set to json::object or else it will
  // be treated as a string
  json settings_json = json::object();

  string tmp_config_filename = backup ? "config.ini" : "config_backup.ini";
  ifstream config_stream(tmp_config_filename);

  // Read to buffer
  stringstream buffer;
  buffer << config_stream.rdbuf();

  // Try saving
  try {

    // Set Settings namespace values
    settings_json = json::parse(buffer.str());
    Settings::enable_detailed_logging =
        settings_json["enable_detailed_logging"].get<bool>();
    // Settings::language = settings_json["language"].get<int>();

  }
  // There's a shitton of exceptions that can be thrown here so I'm catching all
  catch (...) {
    LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent,
                              "Error loading settings.");
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
    error_message = UIState::i18_object.tr("Error") + ": " + tmp_dir.string() +
                    " " + UIState::i18_object.tr("does_not_exist_folder");
    return -1;
  }

  // Can read from?
  bool can_read = true;
  try {
    directory_iterator it(tmp_dir);
    can_read = true;
  } catch (const filesystem_error) {
    can_read = false;
    error_message = UIState::i18_object.tr("Error") + ": " +
                    UIState::i18_object.tr("cannot_read_from") +
                    tmp_dir.string();
  }

  // Can write to?
  bool can_write = true;
  try {
    // Create tmp file in directory and attempt to write to it
    path tmp_file = tmp_dir / "permissions_check.tmp";
    ofstream tmp_stream(tmp_file);
    tmp_stream << "test";
  } catch (filesystem_error) {
    can_write = false;
    error_message = UIState::i18_object.tr("Error") + ": " +
                    UIState::i18_object.tr("cannot_write_to") +
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
    error_message = UIState::i18_object.tr("Error") + ": " + tmp_dir.string() +
                    UIState::i18_object.tr("does_not_exist_file");
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
    error_message = UIState::i18_object.tr("Error") + ": " +
                    UIState::i18_object.tr("cannot_read") + tmp_dir.string();
    return -1;
  }

  return 0;
}

} // namespace Settings
