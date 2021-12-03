#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "types.hpp"

namespace td {
  class Application {
    public:
    Application();

    int run();

    void LaunchMainMenu();

    void drawShopGui();

    void StyleButtonBrown(tgui::Button::Ptr button);

    void HandleMainMenu();

    void QuitPressed();

    private:
    sf::RenderWindow window_;
    tgui::Gui gui_{window_};
    types::AppState state_;

  };
}  // namespace td
