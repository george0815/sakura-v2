// this project
#include "general_views.h"
#include "../../state.h"
#include "../main_screen/bottom_row/submenus/controls/controls_component.h"
#include "../main_screen/bottom_row/submenus/log/log_component.h"

// std
#include <string>
#include <vector>

// SDL3
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace std;
using namespace UIState; // i18n_object

//==========================
//
// This namespace is for general compenents that will be resused.
//
// Current memebers: FocusableTextComponent, TableHeader, AddRow,
// TableComponent, ControlOptionComponent, ColorComponent, TextInputComponent,
// LanguageComponent, Padding
//
//==========================

// Color entries
std::vector<std::string> color_entries;

// Language entries
std::vector<std::string> lang_entries;

namespace GeneralViews {

//==========================
// TEXT COMPONENTS
//==========================

// Just a component used for padding
Component Padding(int padding) {
  return Renderer([padding] { return text(format("{:^{}}", "", padding)); });
}

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
Component ControlOptionComponent(string str, int &control_setting,
                                 string &label) {

  return Container::Horizontal({

             // Used as a label
             Renderer([str] { return text(" " + format("{:<{}}", str, 25)); }),

             // User clicks button -> wait for input -> next input is the value
             // of the
             // NES control being configured

             Button(
                 &label,
                 [&label] {
                   // Set label while waiting for input
                   label = "...";
                   waiting_for_input = true;
                 },
                 ButtonOption::Ascii()),

         }) |
         CatchEvent([&label, &control_setting](Event event) {
           // Ignore mouse events
           if (event.is_mouse()) {
             return false;
           }

           // Only while waiting for input get the key, without this it will
           // catch any key the user types while the button is focused
           if (waiting_for_input == true) {
             label = event.character();
             waiting_for_input = false;

             // Translate to SDL3 key code
             control_setting = ControlsComponent::KeyCodeToSDL3(event);

             return true;
           }

           return false;
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

  color_entries = {i18n_object.tr("Black"),   i18n_object.tr("Blue"),
                   i18n_object.tr("Red"),     i18n_object.tr("Green"),
                   i18n_object.tr("Cyan"),    i18n_object.tr("Pink"),
                   i18n_object.tr("Orange"),  i18n_object.tr("Gray"),
                   i18n_object.tr("HotPink"), i18n_object.tr("White")};

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
  lang_entries = {i18n_object.tr("English"), i18n_object.tr("Japanese")};

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
  comp->ChildAt(0)->Add(FocusableTextComponent(column1));

  // Add second column text
  comp->ChildAt(2)->Add(FocusableTextComponent(column2));

  // Add third column text
  comp->ChildAt(4)->Add(FocusableTextComponent(column3));
}

// Returns a table component consisting of 3 columns, separated by a vertical
// divider (I know I can generalize this for tables that aren't 3 columns, but
// coincidentally all the tables in this UI use 3)
Component TableComponent(string column1, string column2, string column3,
                         int padding, int &selected_tab) {

  return Container::Horizontal({

      // Column 1
      TableHeader(column1, padding, selected_tab),
      Renderer([&] { return separator(); }),

      // Column 2
      TableHeader(column2, padding, selected_tab),
      Renderer([&] { return separator(); }),

      // Column 3 (for some reason whenever I tried to use flex on column3 it
      // would make all its children disappear, so I have an empty
      // Container::Vertical as a hack for now) TODO: Fix this
      TableHeader(column3, padding, selected_tab),
      Container::Vertical(
          {Renderer([&] { return vbox({text(""), separator()}); })}) |
          flex,

  });
}

} // namespace GeneralViews
