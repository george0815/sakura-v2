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

namespace Settings {

// Serializes settings namespace to JSON
int save_settings() {

  json settings_json;

  settings_json["enable_detailed_logging"] = Settings::enable_detailed_logging;

  ofstream test("test");
  test << settings_json;

  return 0;
}

// Serializes settings namespace to JSON
int load_settings() {

  json settings_json = json::object();

  ifstream test("test");

  stringstream buffer;
  buffer << test.rdbuf(); // TODO:: Clean this up later

  try {
    ifstream test("test");

    stringstream buffer;
    buffer << test.rdbuf();

    settings_json = json::parse(buffer.str());
    Settings::enable_detailed_logging =
        settings_json["enable_detailed_logging"].get<bool>();

  } catch (...) {
    save_settings();
    ifstream test("test");

    stringstream buffer;
    buffer << test.rdbuf();
    settings_json = json::parse(buffer.str());
    Settings::enable_detailed_logging =
        settings_json["enable_detailed_logging"].get<bool>();
  }

  return 0;
}

} // namespace Settings
