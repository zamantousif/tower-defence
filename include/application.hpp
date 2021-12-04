#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "types.hpp"
#include <string>

namespace td {
  class Application {
    public:
    Application();

    int run();

    void LaunchMainMenuGui();

    void LaunchMapSelectGui();

    void LaunchGameGui();

    void LaunchOptionsGui();

    void LaunchPauseGui();

    void StyleButtonBrown(tgui::Button::Ptr button);

    void LaunchGame(std::string map_name);

    void HandleMainMenuGui();

    void HandleMapSelectGui();

    void HandleGameGui();

    void HandleOptionsGui();

    void HandlePauseGui();

    private:
    sf::RenderWindow window_;
    tgui::Gui gui_{window_};
    types::AppState state_;

  };
}  // namespace td
