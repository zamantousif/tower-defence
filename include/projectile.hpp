#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "enemy.hpp"
#include "object.hpp"

namespace td {
class Game;
class Enemy;
class Projectile : public Object {
 public:
  /// \brief Projectile constructor
  /// \param position Position of the projectile
  /// \param hitbox   Radius of the circular region occupied by the projectile
  /// \param texture             Texture of the projectile
  /// \param rotation_angle      Orientation, in radians of the projectile
  /// \param damage              Damage % of the projectile
  /// \param is_armor_piercing   Status of projectile armor
  /// \param piercing            Number of enemies pierced by the projectile
  /// before disappearing
  Projectile(types::Position position, float hitbox, sf::Texture* texture,
             float rotation_angle, float damage, bool is_armor_piercing,
             unsigned int piercing, float speed, float lifetime);

  virtual void Update(types::Time dt, std::list<Enemy>& enemies,
                      std::list<Projectile>& projectiles);

  void Update(types::Time dt);

  /// \brief Get the damage value of the projectile
  /// \return Damage value of the projectile
  float getDamage() const;

  /// \brief Get the armor piercing status of the projectile
  /// \return True if projectile has armor piercing active, false otherwise
  bool isArmorPiercing() const;

  /// \brief Set the number of enemies pierced by the projectile
  /// \param count    Number of enemies pierced by the projectile
  void setPiercingLeft(unsigned int count);

  /// \brief Get the speed value of the projectile
  /// \return Speed value of the projectile
  float getSpeed() const;

  /// \brief Get the lifetime the projectile has left
  /// \return How far the projectile can still travel
  float getLifetimeLeft() const;

  /// \brief Get the number of enemies pierced by the projectile
  /// \return Number of enemies pierced by the projectile
  unsigned int getPiercingLeft() const;

 protected:
  float damage_;            ///< Damage value of the projectile
  bool is_armor_piercing_;  ///< Armor piercing status of the projectile
  unsigned int piercing_left_;  ///< Number of enemies pierced by the
                                      ///< projectile before disappearing
  float speed_;              ///< Speed of the projectile
  float lifetime_left_;      ///< How much distance the projectile can still travel before disappearing
};
}  // namespace td
