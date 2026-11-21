
// std
#include <string>

// ftxui
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;
using namespace std;

namespace GeneralViews {

//==========================
// TEXT COMPONENTS
//==========================

// Just a component used for padding
Component Padding(int padding = 0);

// Returns focusble text as component, used for tables (see more detiled comment
// in definition)
Component FocusableTextComponent(string str, int padding = 3);

//==========================
// SETTINGS COMPONENTS
//==========================

// Used in the controls submenu, consists of a Container::Horizontal with a text
// element and a button
Component ControlOptionComponent(string str, int &control_setting,
                                 string &label);

// Used in the settings submenu, consists of a Container::Vertical, with another
// Container::Vertical for store each path text element, then a
// Container::Horizontal for store the add/delete path buttons and the input.
Component RomPathsButtonContainer(string &path);
Component RomPathsContainer(string label);

// Holds final RomPathsComponent
inline Component RomPathsSubComponent = nullptr;

// Add entry to rom path list
void AddRomPathEntry(string path);

// Used in the settings submenu, consists of a Container::Horizontal with a text
// element and an input component
Component TextInputComponent(string label, string &var);

// Used in the settings submenu, consists of a Container::Horizontal with a text
// element and an dropdown component
Component ColorComponent(string str, int &selection);

// Used in the settings submenu, consists of a Container::Horizontal with a text
// element and an dropdown component
Component LanguageComponent(string str, int &selection);

//==========================
// TABLE COMPONENTS
//==========================

// Returns a table header (text + seperator) (see more detiled comment
// in definition)
Component TableHeader(string str, int padding, int &selected_tab);

// Given table component as reference, adds row to that table
void AddRow(Component &comp, string column1, string column2, string column3);

// Returns table component given header string values
Component TableComponent(string column1, string column2, string column3,
                         int padding, int &selected_tab);

} // namespace GeneralViews
