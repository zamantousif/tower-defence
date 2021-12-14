#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "tower.hpp"
#include "collision.hpp"


namespace td {
///  \brief //Implementation of our most basic tower type
class Basic_tower : public Tower {
 public:
  /// \brief                 Basic_tower constructor
  /// \param position        Position of the tower
  /// \param rotation_angle  Orientation, in radians of the tower
  Basic_tower(types::Position position, float rotation_angle = 0.0f, sf::Texture* texture = nullptr, sf::Texture* texture_projectile = nullptr);

  /// \brief Upgrades the tower once
  void Upgrade();

  /// \brief Add projectiles shoot by the tower to the list of all projectiles
  /// \return List of all projectiles currently in game
  bool Shoot(std::list<Projectile>&, std::list<Enemy>& enemies);
};
}  // namespace td
