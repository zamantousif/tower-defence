#pragma once

#include <SFML/Graphics.hpp>

#include "object.hpp"

namespace td {
class Game;
class Projectile : public Object {
 public:
  /// \brief Projectile constructor
  /// \param position Position of the projectile
  /// \param hitbox   Radius of the circular region occupied by the projectile
  /// \param texture             Texture of the projectile
  /// \param rotation_angle      Orientation, in radians of the projectile
  /// \param damage              Damage % of the projectile
  /// \param is_armor_piercing   Status of projectile armor
  /// \param enemy_pierced_count Number of enemies pierced by the projectile
  /// before disappearing
  Projectile(types::Position position, float hitbox, sf::Texture* texture,
             float rotation_angle, float damage, bool is_armor_piercing,
             unsigned int enemy_pierced_count);

  virtual void Update(types::Time dt, const td::Game&); 

  /// \brief Get the damage value of the projectile
  /// \return Damage value of the projectile
  float getDamage() const;

  /// \brief Get the armor piercing status of the projectile
  /// \return True if projectile has armor piercing active, false otherwise
  bool isArmorPiercing() const;

  /// \brief Set the number of enemies pierced by the projectile
  /// \param count    Number of enemies pierced by the projectile
  void setEnemyPiercedCount(unsigned int count);

  /// \brief Get the number of enemies pierced by the projectile
  /// \return Number of enemies pierced by the projectile
  unsigned int getEnemyPiercedCount() const;

  bool isExhausted() const;

 protected:
  float damage_;            ///< Damage value of the projectile
  bool is_armor_piercing_;  ///< Armor piercing status of the projectile
  unsigned int enemy_pierced_count_;  ///< Number of enemies pierced by the
                                      ///< projectile before disappearing
  bool exhausted_;  ///< Projectile is exhausted if it should not make it to the
                    ///< next frame
};
}  // namespace td::projectiles
