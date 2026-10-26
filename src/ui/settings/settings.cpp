#include "settings.h"
#include <fstream>
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
//         TODO: Move verfiy fucntions here

namespace Settings {

// Serializes settings namespace to JSON
int save_settings(bool backup) {

  // Declare json object
  json settings_json;

  // Set values in json object
  settings_json["enable_detailed_logging"] = Settings::enable_detailed_logging;

  // Create and write to file, either main or create a backup
  string tmp_config_filename = backup ? "config.ini" : "config_backup.ini";
  ofstream config_stream(tmp_config_filename);
  config_stream << settings_json;

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

  }
  // There's a shitton of exceptions that can be thrown here so I'm catching all
  catch (...) {
    save_settings(false);

    // Reopen file after it has been saved
    ifstream config_stream("config.ini");

    stringstream buffer;
    buffer << config_stream.rdbuf();
    settings_json = json::parse(buffer.str());

    // Retry setting global values TODO:: Make one function that takes in a json
    // object and sets the global settings values
    Settings::enable_detailed_logging =
        settings_json["enable_detailed_logging"].get<bool>();
  }

  // Return 0 if sucessful
  return 0;
}

// Verifies if a given string is 1. A proper directory, 2. Exists, and 3. Can be
// written to/read from
int VerifyFolder(string directory, string &error_message) {

  // Either not a folder or doesn't exist in the first place
  path tmp_dir = directory;
  if (tmp_dir.empty() || !is_directory(tmp_dir)) {
    return -1;
  }

  // Check folder perms
  perms tmp_dir_permissions = status(tmp_dir).permissions();
  bool can_read = true, can_write = true;

  if (!can_read || !can_write) {

    // Can read from?
    try {
      directory_iterator it(tmp_dir);
      can_read = true;
    } catch (const filesystem_error) {
      can_read = false;
    }

    // Can write to?
    try {

      // Create tmp file in directory and attempt to write to it
      path tmp_file = tmp_dir / "permissions_check.tmp";
      ofstream tmp_stream(tmp_file);
      tmp_stream << "test";
    } catch (filesystem_error) {
      can_write = false;
    }

    return -1;
  }

  return 0;
}

} // namespace Settings
