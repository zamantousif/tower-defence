#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "tower.hpp"

namespace td {
///  \brief //Implementation of the slowing tower that slows down enemies in its
///  range
class Slowing_tower : public Tower {
 public:
  /// \brief                 Slowing_tower constructor
  /// \param position        Position of the tower
  /// \param rotation_angle  Orientation, in radians of the tower
  Slowing_tower(sf::Vector2<float> position, float rotation_angle = 0.0f, sf::Texture* texture = nullptr);

  /// \brief Upgrades the tower once
  void Upgrade();

  /// \brief Add projectiles shoot by the tower to the list of all projectiles
  /// \return List of all projectiles currently in game
  bool Shoot(std::list<Projectile>&, std::list<Enemy>& enemies);
};
}  // namespace td