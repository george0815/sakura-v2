
#include "roms_component.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

#include "../../../../general/general_views.h"

using namespace ftxui;

void RomsComponent::AddRow() {

  // Add name
  RomsComponent::test->ChildAt(0)->Add(Renderer([&](bool focuesd) {
    if (focuesd) {

      return text(" Mario ") | bgcolor(Color::White);
    }

    return text(" Mario ");
  }));

  // Add path
  string test = "gferewr";
  RomsComponent::test->ChildAt(2)->Add(
      GeneralViews::FocusableTextComponent(test));

  // Add SRAM data path
  RomsComponent::test->ChildAt(4)->Add(
      Renderer([&] { return text(" test sram path "); }));
}

Component RomsComponent::RomTableComponent() {

  return Container::Horizontal({

      Container::Vertical({Renderer([&](bool focused) {
        if (focused) {

          return vbox({text("  Name  ") | bgcolor(Color::White), separator()});
        }

        return vbox({text("  Name  "), separator()});
      })}),

      Renderer([&] { return separator(); }),
      Container::Vertical(
          {Renderer([&] { return vbox({text("  Path  "), separator()}); })}),

      Renderer([&] { return separator(); }),
      Container::Vertical({Renderer(
          [] { return vbox({text("  SRAM Data Path  "), separator()}); })

      }),

      Container::Vertical(
          {Renderer([&] { return vbox({text(""), separator()}); })}) |
          flex,

  });
}
