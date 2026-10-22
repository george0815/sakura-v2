#include "settings.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>

using namespace nlohmann;

using namespace std;

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

namespace Settings {

// Serializes settings namespace to JSON
int save_settings() {

  // Declare json object
  json settings_json;

  // Set values in json object
  settings_json["enable_detailed_logging"] = Settings::enable_detailed_logging;

  // Create and write to file
  ofstream config_stream("config.ini");
  config_stream << settings_json;

  return 0;
}

// Serializes settings namespace to JSON
int load_settings() {

  // Create json object as object, has to be set to json::object or else it will
  // be treated as a string
  json settings_json = json::object();

  ifstream config_stream("config.ini");

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
    save_settings();

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

} // namespace Settings
