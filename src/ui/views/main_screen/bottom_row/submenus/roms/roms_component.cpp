
#include "roms_component.h"
#include "../../../../../../core/CART/CART.h"
#include "../../../../../settings/settings.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"
#include "../log/log_component.h"
#include <filesystem>
#include <iostream>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <ranges>
#include <vector>

//==========================
//
// Rom Component, as of now just returns a table but as settings are implemented
// and the emulator is built out more behavior will be added
//
// Current memebers: RomTableComponent, StartRom, LoadAllRoms, LoadRomFolder
//
//==========================

// TODO: Implement start rom, LoadRomFolder

using namespace ftxui;
using namespace std;
using namespace filesystem;

namespace RomsComponent {

// Calls LoadRomFolder on all applicable folders
void LoadAllRoms() {

  // Call LoadRomFolder on default
  LoadRomFolder(Settings::default_rom_path);

  // Loop through rom paths list and call LoadRomFolder on each one (note: rom
  // paths is not a list but a string separated by new line characters)
  // TODO: Low priority: Instead of having the rom paths be a single string,
  // with it being represented in the UI as a text input, implement it as a
  // container vertical with a vector<string> backing it, with add/remove paths
  // buttons
  vector<string> folders =
      views::split(Settings::roms_paths, "\n") | ranges::to<vector<string>>();
  if (!folders.empty()) {
    for (string dir : folders) {
      LoadRomFolder(dir);
    }
  }
}

// Opens folder to directory that the rom currently resides in
void OpenRomFolder() {

  // Get path of rom to start by getting selected index of the rom table, then
  path tmp_path =
      RomsComponent::RomList.at(UIState::SelectedRomTableIndex - 1).path;
  string tmp = tmp_path.parent_path();

  // Sends error_message to log on failure
  string error_message = "";
  if (Settings::OpenFolder(tmp, error_message) != 0) {
    LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent, error_message);
  }
}

// Opens folder to directory that the rom's SRAM file currently resides in
void OpenSRAMFolder() {}

// Verifies directory, searches through and verifies any roms in that directory
void LoadRomFolder(string directory) {

  // Call verify function on default rom directory
  string error_message;
  if (Settings::VerifyFolder(directory, error_message) == 0) {

    // Loop through files in directory (note: non-recursive)
    Rom tmp_rom;
    for (directory_entry tmp_entry : directory_iterator((path)directory)) {

      // If file is valid, create entry and add to list
      if (Settings::VerifyFile(tmp_entry.path(), error_message) == 0 &&
              (tmp_entry.path().extension() == ".nes") ||
          tmp_entry.path().extension() == ".NES") {

        // Create tmp rom entry, pass in values
        tmp_rom = {tmp_entry.path().stem(), tmp_entry.path(),
                   tmp_entry.file_size()};

        // Push to list and log
        RomList.push_back(tmp_rom);
        LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent,
                                  UIState::i18_object.tr("Rom_added:_") +
                                      tmp_rom.name);

        // Add row in UI;
        GeneralViews::AddRow(RomSubmenuComponent, tmp_rom.name, tmp_rom.path,
                             to_string(tmp_rom.size));

        // If nes rom fails to verify
      } else if (Settings::VerifyFile(tmp_entry.path(), error_message) != 0 &&
                 (tmp_entry.path().extension() == ".nes" ||
                  tmp_entry.path().extension() == ".NES")) {
        // Adds error message to log
        LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent,
                                  error_message);
      } // non .nes files are ignored
    }

  } else {
    // Adds error message to log
    LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent, error_message);
  }
}

// Launches rom for now using the old sakura core until the new one is done
void StartRom() {

  // Get path of rom to start by getting selected index of the rom table, then
  string tmp =
      "/home/Hunter/Documents/Github/sakura/sakura " +
      RomsComponent::RomList.at(UIState::SelectedRomTableIndex - 1).path;

  LogComponent::AddLogEntry(
      LogComponent::LogSubmenuComponent,
      UIState::i18_object.tr("Roms_started:_") +
          RomsComponent::RomList.at(UIState::SelectedRomTableIndex - 1).name);

  int result = system(tmp.c_str());
}

// Simple roms table
Component RomTableComponent() {
  return GeneralViews::TableComponent(
      UIState::i18_object.tr("Name"), UIState::i18_object.tr("Path"),
      UIState::i18_object.tr("Size"), 3, UIState::SelectedRomTableIndex);
}

} // namespace RomsComponent
