#pragma once

#include <SFML/Graphics.hpp>

/// \brief Define types useful to our game.
namespace td::types {
using Position =
    sf::Vector2f;  ///< The type that stores the position of any game object.
using Texture =
    sf::Texture;  ///< The type that stores the texture of any game object.
using Time = sf::Time;  ///< The type that stores the time.

enum AppState { kMainMenu, kOptions, kMapSelect, kGame, kPause, kUpgrade };
}  // namespace td::types
