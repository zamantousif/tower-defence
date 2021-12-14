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
  Bomb_projectile(types::Position position, float rotation_angle, int damage,
                  sf::Texture* texture_projectile, sf::Texture* texture_explosion);

//  void Update(td::types::Time dt) override;

private:
sf::Texture* texture_explosion_;  ///<Texture of the explosion of the bomb
};
}  // namespace td::projectiles
