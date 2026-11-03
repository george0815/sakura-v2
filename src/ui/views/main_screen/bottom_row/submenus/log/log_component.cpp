
#include "log_component.h"
#include "../../../../../state.h"
#include "../../../../general/general_views.h"

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
// Current memebers: AddLogEntry, LogComponent
//
//==========================

using namespace GeneralViews; // FocusableTextComponent
using namespace UIState;      // most_recent_log, i18_object

namespace LogComponent {

// Uses GeneralViews::AddFocusableText to add a log Entry
void AddLogEntry(string str) {
  LogSubmenuComponent->Add(FocusableTextComponent(str));
  // Update header
  most_recent_log = " " + str;
}

// Returns log component, basically just a Container::Vertical
Component LogComponent() {
  return Container::Vertical({{

      // It was seg faulting unless I had at least one component here, so the
      // log will always start with this entry
      FocusableTextComponent(i18n_object.tr("sakura_init")),

  }});
}

} // namespace LogComponent
