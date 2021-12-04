#pragma once

#include "object.hpp"
#include "types.hpp"

namespace td {
///  \brief Tower class represents the blueprint of a basic tower in the game.
///  The base tower class can be derived further to create towers with special
///  powers.
class Tower : public Object {
 public:
  /// \brief Tower constructor
  /// \param position       Position of the tower
  /// \param hitbox         Radius of the circular region occupied by the tower
  /// \param texture        Texture of the tower
  /// \param attack_speed   Attack speed of the tower
  /// \param range          Attack range of the tower
  Tower(types::Position position, float hitbox, types::Texture* texture,
        float rotation_angle = 0.0f, unsigned int attack_speed = 1U,
        float range = 1.0f);

  /// \brief Tower constructor
  /// \param position     Position of the tower
  /// \param attack_speed  Attack speed of the tower
  explicit Tower(types::Position position, float rotation_angle,
                 unsigned int attack_speed);

  /// \brief Get the attack speed of the tower
  /// \return Attack speed of the tower
  virtual unsigned int getAttackSpeed() const;

  /// \brief Get the attack range of the tower
  /// \return Attack range of the tower
  virtual float getRange() const;

 protected:
  unsigned int attack_speed_;  ///< Attack speed of the tower
  float range_;                ///< Attack range of the tower
};
}  // namespace td
