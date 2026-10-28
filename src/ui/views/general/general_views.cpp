#include "general_views.h"
#include "../../state.h"

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <vector>

using namespace std;

// TODO:: i18n

//==========================
//
// This namespace is for general compenents that will be resused.
//
// Current memebers: FocusableTextComponent, TableHeader, AddRow,
// TableComponent, ControlOptionComponent, ColorComponent, TextInputComponent,
// LanguageComponent
//
//==========================

// Color entries
std::vector<std::string> color_entries;

// Language entries
std::vector<std::string> lang_entries;

namespace GeneralViews {

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

//==========================
// SETTINGS COMPONENTS
//==========================

// Used in the controls submenu, consists of a Container::Horizontal with a text
// element and a button
Component ControlOptionComponent(string str, int &control_setting) {

  string button_label = str;

  return Container::Horizontal({

      // Used as a label
      Renderer([str] { return text(" " + format("{:<{}}", str, 25)); }),

      // User clicks button -> wait for input -> next input is the value of the
      // NES control being configured TODO:: Replace logic once settings are
      // implemented

      Button(
          &UIState::test_button_label,
          [&] { UIState::test_button_label = "..."; }, ButtonOption::Ascii()),

  });
}

// Used in the settings submenu, consists of a Container::Horizontal with a text
// element and an input component
Component TextInputComponent(string label, string &var) {

  return Container::Horizontal({

             // Used as a label
             Renderer([label] {
               return text(" " + format("{:<{}}", label, 30));
             }) | center,
             // For some reason the color decorator refuses to work, so I can't
             // make inputs have a white background since the actual text wont
             // be visible
             Input(&var)}) |
         border;
}

// Used in the settings submenu, consists of a Container::Horizontal with a text
// element and an dropdown component
Component ColorComponent(string str, int &selection) {

  color_entries = {UIState::i18_object.tr("Black"),
                   UIState::i18_object.tr("Blue"),
                   UIState::i18_object.tr("Red"),
                   UIState::i18_object.tr("Green"),
                   UIState::i18_object.tr("Cyan"),
                   UIState::i18_object.tr("Magenta"),
                   UIState::i18_object.tr("Brown"),
                   UIState::i18_object.tr("Gray"),
                   UIState::i18_object.tr("BrightBlue"),
                   UIState::i18_object.tr("BrightGreen"),
                   UIState::i18_object.tr("BrightCyan"),
                   UIState::i18_object.tr("BrightRed"),
                   UIState::i18_object.tr("BrightMagenta"),
                   UIState::i18_object.tr("BrightYellow"),
                   UIState::i18_object.tr("White")};

  return Container::Horizontal({

      // Used as a label
      Renderer([str] { return text(" " + format("{:<{}}", str, 30)); }) |
          center,
      Dropdown(&color_entries, &selection)

  });
}

// Used in the settings submenu, consists of a Container::Horizontal with a text
// element and an dropdown component
Component LanguageComponent(string str, int &selection) {

  // Sets up language options
  lang_entries = {UIState::i18_object.tr("English"),
                  UIState::i18_object.tr("Japanese")};

  return Container::Horizontal({

      // Used as a label
      Renderer([str] { return text(" " + format("{:<{}}", str, 30)); }) |
          center,
      Dropdown(&lang_entries, &selection)

  });
}

//==========================
// TABLE COMPONENTS
//==========================

// Returns a table header that consists of the text and the lower separator

Component TableHeader(string str, int padding, int &selected_tab) {

  // Calculate padding amount from str len
  int final_padding_amount = padding + str.length();

  // Doesnt matter if headers are focusable, so focused bool isn't needed
  return Container::Vertical(
      {
          Renderer([str, final_padding_amount]() {
            return vbox(
                // To be honest the format syntax is still a mystery to me, the
                // docs said do this so I did
                {text(format("{:^{}}", str, final_padding_amount)),
                 separator()});
          }),
      }

      ,
      &selected_tab);
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
                         int padding, int &selected_tab) {

  return Container::Horizontal({

      // Column 1
      GeneralViews::TableHeader(column1, padding, selected_tab),
      Renderer([&] { return separator(); }),

      // Column 2
      GeneralViews::TableHeader(column2, padding, selected_tab),
      Renderer([&] { return separator(); }),

      // Column 3 (for some reason whenever I tried to use flex on column3 it
      // would make all its children disappear, so I have an empty
      // Container::Vertical as a hack for now) TODO: Fix this
      GeneralViews::TableHeader(column3, padding, selected_tab),
      Container::Vertical(
          {Renderer([&] { return vbox({text(""), separator()}); })}) |
          flex,

  });
}

} // namespace GeneralViews
