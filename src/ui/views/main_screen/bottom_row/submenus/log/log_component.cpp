
#include "log_component.h"
#include "../../../../../settings/settings.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"
#include <iostream>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

//==========================
//
// This namespace is for the log submenu and any logic that is associated
// with it.
//
// Current members: AddLogEntry, LogComponent
//
//==========================

using namespace GeneralViews; // FocusableTextComponent
using namespace UIState;      // MostRecentLog, I18nObject
using namespace std;          // cout

namespace LogComponent {

// Uses GeneralViews::AddFocusableText to add a log Entry
void AddLogEntry(string str) {

  // Do nothing and return early if emulation logging is off and a rom is
  // currently begin emulated
  if (CurrentlyEmulating && !Settings::EnableEmulationLogging) {
    return;
  }
  // I check if its a nullptr here because CART is used by sakura_v2_tests, but
  // sakura_v2_tests doesn't set up the UI so AddLogEntry (which is called in
  // CART's functions) would lead to a segfault here if called in the tests.
  if (LogSubmenuComponent != nullptr) {
    LogSubmenuComponent->Add(FocusableTextComponent(str));
    // Update header and add log to vector
    MostRecentLog = " " + str;
    LogVector.push_back(str);
  } else {
    cout << str << endl;
  }
}

// Returns log component, basically just a Container::Vertical
Component LogComponent() {
  return Container::Vertical({{

      // It was seg faulting unless I had at least one component here, so
      // the
      // log will always start with this entry
      FocusableTextComponent(I18nObject.tr("sakura_init")),

  }});
}

} // namespace LogComponent
