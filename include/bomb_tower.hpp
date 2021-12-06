#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "tower.hpp"

namespace td {
///  \brief //Implementation of bomb tower that shoots explosive bombs to
///  enemies
class Bomb_tower : public Tower {
 public:
  /// \brief                 Bomb_tower constructor
  /// \param position        Position of the tower
  /// \param rotation_angle  Orientation, in radians of the tower
  Bomb_tower(sf::Vector2<float> position, float rotation_angle = 0.0f,
             sf::Texture* texture = nullptr,
             sf::Texture* texture_projectile = nullptr);

  /// \brief Add projectiles shoot by the tower to the list of all projectiles
  /// \return List of all projectiles currently in game
  std::list<projectiles::Projectile> shoot(std::list<projectiles::Projectile>);
};
}  // namespace td
