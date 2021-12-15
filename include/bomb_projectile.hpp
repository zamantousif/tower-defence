#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.hpp"

namespace td {
class Bomb_projectile : public Projectile {
 public:
  /// \brief                 Bomb_projectile constructor
  /// \param position        Position of the projectile
  /// \param rotation_angle  Orientation, in radians of the projectile
  /// \param damage          Damage % of the projectile
  /// \param texture_projectile  Pointer to the texture of the projectile
  /// \param texture_explosion  Pointer to the texture of the explosion of the bomb
  Bomb_projectile(types::Position position, float rotation_angle, int damage,
                  sf::Texture* texture_projectile, sf::Texture* texture_explosion,
                  float speed, float lifetime);

private:
sf::Texture* texture_explosion_;  ///<Texture of the explosion of the bomb
};
}  // namespace td
