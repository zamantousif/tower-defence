#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.hpp"

namespace td::projectiles {
class Strong_projectile : public Projectile {
 public:
  /// \brief                 Strong_projectile constructor
  /// \param position        Position of the projectile
  /// \param rotation_angle  Orientation, in radians of the projectile
  Strong_projectile(sf::Vector2<float> position, float rotation_angle);

  void Update(td::types::Time dt) { (void)dt; }
};
}  // namespace td::projectiles