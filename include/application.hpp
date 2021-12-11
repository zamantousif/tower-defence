#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <map>
#include <optional>
#include <string>

#include "collision.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "object.hpp"
#include "projectile.hpp"
#include "tower.hpp"
#include "types.hpp"
//#include "constants.hpp"

namespace td {
/// \brief Application class represents the app that runs the game. It takes
/// care of the game's gui and rendering.
class Application {
 public:
  /// \brief Application constructor
  Application();

  /// \brief Runs the application
  int run();

  /// \brief Loads all of the game's textures into textures_
  void LoadTextures();

  /// \brief Creates TGUI widgets for the main menu
  void LaunchMainMenuGui();

  /// \brief Creates TGUI widgets for the map selection screen
  void LaunchMapSelectGui();

  /// \brief Creates TGUI widgets for the game gui
  void LaunchGameGui();

  /// \brief Creates TGUI widgets for the options menu
  void LaunchOptionsGui();

  /// \brief Creates TGUI widgets for the pause menu
  void LaunchPauseGui();

  /// \brief Creates TGUI widgets for tower upgrading
  void LaunchUpgradeGui();

  /// \brief Creates TGUI widgets for the main menu
  void LaunchGame(std::string map_name);

  /// \brief Closes the game and returns to main menu. Takes care of deletion of
  /// objects.
  void CloseGame();

  /// \brief Handles events and draws sprites when in the main menu
  void HandleMainMenu();

  /// \brief Handles events and draws sprites when in map select
  void HandleMapSelect();

  /// \brief Handles events and draws sprites when in-game
  void HandleGame();

  /// \brief Handles events and draws sprites when in the options menu
  void HandleOptions();

  /// \brief Handles events and draws sprites when in the pause menu
  void HandlePause();

  /// \brief Handles events and draws sprites when upgrading a tower
  void HandleUpgrade();

  /// \brief Handles TGUI signals of the main menu gui
  void HandleMainMenuGui();

  /// \brief Handles TGUI signals of the map select gui
  void HandleMapSelectGui();

  /// \brief Handles TGUI signals of the game gui
  void HandleGameGui();

  /// \brief Handles TGUI signals of the options menu gui
  void HandleOptionsGui();

  /// \brief Handles TGUI signals of the pause menu gui
  void HandlePauseGui();

  /// \brief Handles TGUI signals of the upgrade menu gui
  void HandleUpgradeGui();

  /// \brief Gui helper function that changes the targeting option of the
  /// currently selected tower "rightwards"
  void TargetingSwitchRight();

  /// \brief Gui helper function that changes the targeting option of the
  /// currently selected tower "leftwards"
  void TargetingSwitchLeft();

  /// \brief Draws towers, projectiles, enemies and their health bars
  void DrawGameElements();

  /// \brief Draws the elements of game gui that go over TGUI elements
  void DrawShopElements();

  /// \brief scales an sf::Sprite to have correct proportions relative to the
  /// window called once for every sprite \param sprite  Sprite that is scaled
  void ScaleSprite(sf::Transformable& sprite);

  /// \brief Changes a tgui::Button to match the game's artstyle
  /// \param button  Button that gets changed
  void StyleButtonBrown(tgui::Button::Ptr button);

 private:
  sf::RenderWindow window_;
  unsigned int window_x_;   // width of the window on creation, could be global
                            // constant instead?
  unsigned int window_y_;   // height of the window on creation
  tgui::Gui gui_{window_};  // Gui object where widgets are added to
  types::AppState state_ =
      types::kOptions;  // tracks the state the application is in
  std::map<std::string, sf::Texture*> textures_;  // map with all loaded
                                                  // textures
  std::optional<Game> game_ = {};
  sf::Font font_;         // font used for sf::Text
  float volume_ = 70.0f;  // value between 0 and 100 that affects the volume of
                          // sound effects
  float music_volume_ = 70.0f;  // value between 0 and 100 that affects the
                                // volume of background music
  Tower* upgrading_tower_ =
      nullptr;  // Tower that currently has its upgrade menu open,
                // nullptr if no tower is being upgraded
  std::optional<Tower> buying_tower_ =
      {};  // Tower that currently has its upgrade menu
           // open, nullptr if no tower is being upgraded
};
}  // namespace td
