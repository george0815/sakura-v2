
#include "roms_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>

using namespace ftxui;

ftxui::Component RomsComponent::RomTableComponent() {

  return

      Renderer([&] {
        auto tmpTable = ftxui::Table(std::vector<std::vector<std::string>>{

            {"Name", "Size"},
            {"Mario", "2GB"},
            {"Kirby", "1GB"},

        });

        tmpTable.SelectAll().Border(LIGHT);
        tmpTable.SelectRow(0).SeparatorVertical(LIGHT);
        tmpTable.SelectRow(0).Decorate(bold);
        tmpTable.SelectColumn(1).Decorate(flex);
        tmpTable.SelectRow(2).Decorate(flex);

        return tmpTable.Render() | flex;
      });
}
