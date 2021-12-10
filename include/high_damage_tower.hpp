#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "tower.hpp"

namespace td {
///  \brief //Implementation of high damage tower that has sparse shooting
///  speed, but does massive damage on one hit.

class High_damage_tower : public Tower {
 public:
  /// \brief                 High_damage_tower constructor
  /// \param position        Position of the tower
  /// \param rotation_angle  Orientation, in radians of the tower
  High_damage_tower(types::Position position, float rotation_angle = 0.0f,
                    sf::Texture* texture = nullptr,
                    sf::Texture* texture_projectile = nullptr);

  /// \brief Add projectiles shoot by the tower to the list of all projectiles
  /// \return List of all projectiles currently in game
  std::list<projectiles::Projectile> shoot(std::list<projectiles::Projectile>, std::vector<Enemy> enemies);

   /// \brief Get the upgrade cost of the tower at current level
  /// \return Upgrade cost of the tower
   unsigned int getUpgradeCost();
};
}  // namespace td
