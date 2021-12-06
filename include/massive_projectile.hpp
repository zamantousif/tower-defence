#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.hpp"

namespace td::projectiles {
class Massive_projectile : public Projectile {
 public:
  /// \brief                 Massive_projectile constructor
  /// \param position        Position of the projectile
  /// \param rotation_angle  Orientation, in radians of the projectile
  /// \param damage          Damage % of the projectile
  Massive_projectile(types::Position position, float rotation_angle,
                     int damage,  sf::Texture* texture_projectile);

  void Update(td::types::Time dt) override;
};
}  // namespace td::projectiles
