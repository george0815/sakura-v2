#include <iostream>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>

int main() {

  using namespace ftxui;

  auto summary = [&] {
    auto content = vbox({

        hbox({text("test")})

    });
    return window(text("Test"), content);
  };

  auto document = vbox({
      hbox({
          summary(),
          summary(),
          summary() | flex,
      }),
      summary(),
      summary(),
  });

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);

  std::cout << screen.ToString() << '\0' << std::endl;

  return EXIT_SUCCESS;
}
