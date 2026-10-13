#include "general_views.h"

// ftxui
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;

//==========================
//
// This namespace is for general compenents that will be resused.
//
// Current memebers: FocusableTextComponent, TableHeader, AddRow, TableComponent
//
//==========================

namespace GeneralViews {

//==========================
// TABLE COMPONENTS
//==========================

// Returns a text comopoent that the use can focus on, this is needed for
// navigating the tables.

Component FocusableTextComponent(string str, int padding) {

  // Calculate padding amount from str len
  int final_padding_amount = padding + str.length();

  // Captures str param, takes in bool focused
  return Renderer([str, final_padding_amount](bool focused) {
    if (focused) {
      return text(format("{:^{}}", str, final_padding_amount)) |
             bgcolor(Color::White) |
             color(Color::Black); // TODO:: After settings are implemented,
                                  // replace colors with the colors determined
                                  // by the settings
    }

    // No else needed since this wont run if focused anyway
    return text(format("{:^{}}", str, final_padding_amount));
  });
}

// Returns a table header that consists of the text and the lower separator

Component TableHeader(string str, int padding) {

  // Calculate padding amount from str len
  int final_padding_amount = padding + str.length();

  // Doesnt matter if headers are focusable, so focused bool isn't needed
  return Container::Vertical({Renderer([str, final_padding_amount]() {
    return vbox(
        // To be honest the format syntax is still a mystery to me, the docs
        // said do this so I did
        {text(format("{:^{}}", str, final_padding_amount)), separator()});
  })}

  );
}

// Given table component as reference, adds a row to that component
void AddRow(Component &comp, string column1, string column2, string column3) {

  // Add first column text
  comp->ChildAt(0)->Add(GeneralViews::FocusableTextComponent(column1));

  // Add second column text
  comp->ChildAt(2)->Add(GeneralViews::FocusableTextComponent(column2));

  // Add third column text
  comp->ChildAt(4)->Add(GeneralViews::FocusableTextComponent(column3));
}

// Returns a table component consisting of 3 columns, separated by a vertical
// divider (I know I can generalize this for tables that aren't 3 columns, but
// coincidentally all the tables in this UI use 3)
Component TableComponent(string column1, string column2, string column3,
                         int padding) {

  return Container::Horizontal({

      // Column 1
      GeneralViews::TableHeader(column1, padding),
      Renderer([&] { return separator(); }),

      // Column 2
      GeneralViews::TableHeader(column2, padding),
      Renderer([&] { return separator(); }),

      // Column 3 (for some reason whenever I tried to use flex on column3 it
      // would make all its children disappear, so I have an empty
      // Container::Vertical as a hack for now)
      GeneralViews::TableHeader(column3, padding),
      Container::Vertical(
          {Renderer([&] { return vbox({text(""), separator()}); })}) |
          flex,

  });
}

} // namespace GeneralViews
