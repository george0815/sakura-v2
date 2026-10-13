
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>

using namespace ftxui;
using namespace std;

namespace GeneralViews {

// Returns focusble text as component, used for tables (see more detiled comment
// in definition)
Component FocusableTextComponent(string str, int padding = 3);

//==========================
// SETTINGS COMPONENTS
//==========================

// Used in the controls submenu, consists of a Container::Horizontal with a text
// element and a button
Component ControlOptionComponent(string str, int index);

// Used in the settings submenu, consists of a Container::Horizontal with a text
// element and an input component
Component TextInputComponent(string label, string &var, int index);

// Used in the settings submenu, consists of a Container::Horizontal with a text
// element and an dropdown component
Component ColorComponent(int index);

//==========================
// TABLE COMPONENTS
//==========================

// Returns a table header (text + seperator) (see more detiled comment
// in definition)
Component TableHeader(string str, int padding);

// Given table component as reference, adds row to that table
void AddRow(Component &comp, string column1, string column2, string column3);

// Returns table component given header string values
Component TableComponent(string column1, string column2, string column3,
                         int padding);

} // namespace GeneralViews
