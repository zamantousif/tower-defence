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

    void DrawShopElements();

    //scales an sf::Sprite to have correct proportions relative to the window
    //called once for every sprite
    void ScaleSprite(sf::Sprite& sprite);

    //Changes a tgui::Button to match the game's artstyle
    void StyleButtonBrown(tgui::Button::Ptr button);

    private:
    sf::RenderWindow window_;
    float window_x_;   //width of the window on creation, could be global constant instead?
    float window_y_;   //height of the window on creation
    tgui::Gui gui_{window_};
    types::AppState state_;    //tracks the state the application is in
    std::map<std::string, sf::Texture*> textures_;  //map with all loaded textures
    sf::Font font_;    //font used for sf::Text
    float volume_;     //value between 0 and 100 that affects the volume of sound effects
    float music_volume_; //value between 0 and 100 that affects the volume of background music
  };
}  // namespace td
