#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <string>

namespace td {
  class Application {
    public:
    Application();

    int run();

    void LaunchMainMenu();

    void drawShopGui();

    private:
    sf::RenderWindow window_;
    tgui::Gui gui_{window_};
  };
}  // namespace td
