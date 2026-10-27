
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

// Verifies directory, searches through and verifies any roms in that directory
void LoadRomFolder(string directory) {

  // Call verify function on default rom directory
  string error_message;
  if (Settings::VerifyFolder(directory, error_message) == 0) {

    cout << directory;
    // Loop through files in directory (note: non-recursive)
    Rom tmp_rom;
    for (directory_entry tmp_entry : directory_iterator((path)directory)) {

      // If file is valid, create entry and add to list
      if (Settings::VerifyFile(tmp_entry.path(), error_message) == 0 &&
              (tmp_entry.path().extension() == ".nes") ||
          tmp_entry.path().extension() == ".NES") {
        tmp_rom = {tmp_entry.path().filename(), tmp_entry.path(),
                   tmp_entry.file_size()};
        RomList.push_back(tmp_rom);
        LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent,
                                  UIState::i18_object.tr("Rom_added:_") +
                                      tmp_rom.name); // TODO: add i18n string
        GeneralViews::AddRow(RomSubmenuComponent, tmp_rom.name, tmp_rom.path,
                             to_string(tmp_rom.size));
      } else if (Settings::VerifyFile(tmp_entry.path(), error_message) != 0 &&
                 (tmp_entry.path().extension() == ".nes" ||
                  tmp_entry.path().extension() == ".NES")) {
        // Adds error message to log
        LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent,
                                  error_message);
      }
    }

  } else {
    // Adds error message to log
    LogComponent::AddLogEntry(LogComponent::LogSubmenuComponent, error_message);
  }
}

void StartRom(Component &comp, int index) {

  // Get focused child of internal Container::Vertical in the table
  cout << UIState::SelectedRomTableIndex;
}

// Simple roms table
Component RomTableComponent() {
  return GeneralViews::TableComponent(
      UIState::i18_object.tr("Name"), UIState::i18_object.tr("Path"),
      UIState::i18_object.tr("Size"), 3, UIState::SelectedRomTableIndex);
}

} // namespace RomsComponent
