
#include "log_component.h"
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
// Current memebers:
//
//==========================

namespace LogComponent {

// Uses GeneralViews::AddFocusableText to add a log Entry
void AddLogEntry(Component &comp, string str) {
  comp->Add(GeneralViews::FocusableTextComponent(str));
}

// Returns log component, basically just a Container::Vertical
Component LogComponent() {
  return Container::Vertical({{

      // It was seg faulting unless I had at least one component here, so the
      // log will always start with this entry
      GeneralViews::FocusableTextComponent("sakura-v2 INIT"),

  }});
}

} // namespace LogComponent
