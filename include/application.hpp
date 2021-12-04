#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "types.hpp"
#include <string>
#include <map>

namespace td {
  class Application {
    public:
    Application();

    int run();

    //Loads all of the game's textures into texture_map_
    void LoadTextures();

    void LaunchMainMenuGui();

    void LaunchMapSelectGui();

    void LaunchGameGui();

    void LaunchOptionsGui();

    void LaunchPauseGui();

    void StyleButtonBrown(tgui::Button::Ptr button);

    void LaunchGame(std::string map_name);

    void HandleMainMenu();

    void HandleMapSelect();

    void HandleGame();

    void HandleOptions();

    void HandlePause();

    void HandleMainMenuGui();

    void HandleMapSelectGui();

    void HandleGameGui();

    void HandleOptionsGui();

    void HandlePauseGui();

    private:
    sf::RenderWindow window_;
    tgui::Gui gui_{window_};
    types::AppState state_;
    std::map<std::string, sf::Texture*> textures_;
    sf::Font font_;    //font used for sf::Text
    float volume_;     //value between 0 and 100 that affects the volume of sound effects
    float music_volume_;
  };
}  // namespace td
