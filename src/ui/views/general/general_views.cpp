#include "general_views.h"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

namespace GeneralViews {

Component FocusableTextComponent(string &str) {

  return Renderer([str](bool focused) {
    if (focused) {
      return text(str) | bgcolor(Color::White) | color(Color::Black);
    }

    return text("fds");
  });
}

} // namespace GeneralViews
