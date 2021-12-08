#pragma once

#include <SFML/Graphics.hpp>

#include "object.hpp"
#include "projectile.hpp"

namespace td {
///  \brief Enemy class represents the blueprint of a basic enemy in the game.
///  The base enemy class can be derived further to create towers with special
///  powers.
class Enemy : public Object {
 public:
  /// \brief Enemy constructor
  /// \param position       Position of the enemy
  /// \param hitbox         Radius of the circular region occupied by the enemy
  /// \param texture        A pointer to the texture of the enemy
  /// \param health         Health of the enemy
  /// \param move_speed     Movement speed of the enemy
  /// \param bounty         Bounty of the enemy
  /// \param armored        Status ofenemy armor
  /// \param moved_distance Total distance moved on the path by the enemy
  /// \param slowed_level   The level by witch the enemy is slowed
  Enemy(types::Position position, float hitbox, sf::Texture* texture,
        float health = 100.0f, int move_speed = 1, float bounty = 0.0f,
        bool armored = false, float distance_moved = 0.0f, unsigned int slowed_level = 0);

  void Update(types::Time dt) override;

  /// \brief Get the remaining health of the enemy
  /// \return Remaining health of the enemy
  virtual float getHealth() const;

  /// \brief Get the movement speed of the enemy
  /// \return Movement speed of the enemy
  virtual int getMoveSpeed() const;


  /// \brief Get the bounty of the enemy
  /// \return Bounty of the enemy
  virtual float getBounty() const;

  /// \brief Status of enemy armor
  /// \return True if the enemy is armored otherwise false
  virtual bool isArmored() const;

  /// \brief Set the total distance moved on the path by the enemy
  virtual void setDistanceMoved(float distance);

  /// \brief Get the distance enemy has travelled
  /// \return Distance the enemy has travelled
  virtual float getDistanceMoved() const;

  /// \brief Set the slowed_level of the enemy
  virtual void setSlowedLevel(unsigned int level);

    /// \brief Get the slowed level of the enemy
  /// \return slowed_level of the enemy
  virtual unsigned int getSlowedLevel() const;

 protected:
  float health_;          ///< Remaining health of the enemy
  int move_speed_;        ///< Movement speed of the enemy
  int bounty_;            ///< Bounty of the enemy
  bool armored_;          ///< Status of enemy armor
  float distance_moved_;  ///< Total distance moved on the path by the enemy
  int slowed_level_;      ///< Level by witch the enemy is slowed
};
}  // namespace td
