#pragma once

#include <SFML/Graphics.hpp>

/// \brief Define types useful to our game.
namespace td::types {
using Position =
    sf::Vector2f;  ///< The type that stores the position of any game object.
using Time = sf::Time;  ///< The type that stores the time.
enum Targeting { kFirst, kLast, kClose, kStrong, kArea };  ///<Targeting settings for towers

enum AppState { kMainMenu, kOptions, kMapSelect, kGame, kPause, kUpgrade };  ///<The different states Application can be in
using BlockedRegion =
    sf::ConvexShape;  ///< Represents a region where towers cannot be placed.
}  // namespace td::types
