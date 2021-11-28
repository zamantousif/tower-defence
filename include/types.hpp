#pragma once

#include <SFML/Graphics.hpp>

/// \brief Define types useful to our game.
namespace td::types {
  using Position = sf::Vector2f; ///< The type that stores the position of any game object.
  using BlockedRegion = sf::ConvexShape; ///< Represents a region where towers cannot be placed.
}
