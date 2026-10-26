
#include "roms_component.h"
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
  if (Settings::VerfyFolder(directory, error_message) == 0) {

    // Loop through files in directory (note: non-recursive)
    for (directory_entry tmp_entry : directory_iterator((path)directory)) {

      // For each file, run verify NES rom function
      // TODO: Create get NES in core (since it will be reused
      // again while initializing the cart)
      //
      // TODO: Create verify file function
      // If pass, create rom struct and add it to roms list

      Rom tmp_rom = {

      };
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
  return GeneralViews::TableComponent(UIState::i18_object.tr("Name"),
                                      UIState::i18_object.tr("Path"),
                                      UIState::i18_object.tr("SRAM data path"),
                                      3, UIState::SelectedRomTableIndex);
}

} // namespace RomsComponent
