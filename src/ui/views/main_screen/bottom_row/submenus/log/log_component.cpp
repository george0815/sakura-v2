
#include "log_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>

using namespace ftxui;

ftxui::Component LogComponent::LogTableComponent() {

  return

      Renderer([&] {
        return ftxui::Table(std::vector<std::vector<std::string>>{

                                {"Time", "Event"},
                                {"23:12", "CHR_ROM init"},
                                {"23:43", "PRG_ROM init"},

                            })
            .Render();
      });
}
