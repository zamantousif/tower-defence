#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.hpp"
#include "types.hpp"

namespace td {
class Basic_projectile : public Projectile {
 public:
  /// \brief                     Basic_projectile constructor
  /// \param position            Position of the projectile
  /// \param rotation_angle      Orientation, in radians of the projectile
  /// \param damage              Damage % of the projectile
  /// \param enemy_pierced_count How many enemies the projectile can hit before
  /// disappearing
  /// \param texture             Pointer to the texture of the projectile
  Basic_projectile(types::Position position, float rotation_angle, int damage,
                   unsigned int enemy_pierced_count, sf::Texture* texture = nullptr);

//  void Update(td::types::Time dt) override;
};
}  // namespace td::projectiles
