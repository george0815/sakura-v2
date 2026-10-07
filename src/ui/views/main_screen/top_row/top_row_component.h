#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

class TopRow {

public:
  Component AsciiBox();

  Component InfoContainer();

  TopRow() {
    TopRowComponent = Container::Horizontal(
        {AsciiBox(), InfoContainer(), ControlsContainer()});
  }

  Component TopRowComponent;

  Component ControlsContainer();
};
