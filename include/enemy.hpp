#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "object.hpp"
#include "projectile.hpp"

namespace td {
class Game;
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
  /// \param slowed_level   The level by which the enemy is slowed
  /// \param melting_level  The level by which the enemy is melted
  Enemy(types::Position position, float hitbox, sf::Texture* texture,
        float health = 100.0f, int move_speed = 1, float bounty = 0.0f,
        bool armored = false, float distance_moved = 0.0f,
        unsigned int slowed_level = 0);

  virtual void Update(types::Time dt, const td::Game&);

  /// \brief Create basic cockroach at the start of the map
  /// \param startOfTheMap  Position of the start of the map
  /// \param texture        Texture of the enemy
  /// \return The basic cockroach
  Enemy createBasicCockroach(types::Position startOfTheMap,
                              sf::Texture* texture);

  /// \brief Create fly at the start of the map
  /// \param startOfTheMap  Position of the start of the map
  /// \param texture        Texture of the enemy
  /// \return The fly
  Enemy createFly(types::Position startOfTheMap, sf::Texture* texture);

  /// \brief Create beetle at the start of the map
  /// \param startOfTheMap  Position of the start of the map
  /// \param texture        Texture of the enemy
  /// \return The beetle
  Enemy createBeetle(types::Position startOfTheMap, sf::Texture* texture);

  /// \brief Create dragonfly (boss enemy) at the start of the map
  /// \param startOfTheMap  Position of the start of the map
  /// \param texture        Texture of the enemy
  /// \return The dragonfly (boss)
  Enemy createDragonfly(types::Position startOfTheMap,
                                sf::Texture* texture);

  /// \brief Get the remaining health of the enemy
  /// \return Remaining health of the enemy
  float getHealth() const;

  /// \brief Set the health of the enemy
  /// \param health_decrease the amount of health that is decreased from enemys
  /// health
  void setHealth(float health_decrease);

  /// \brief Get the maximum health of the enemy
  /// \return Maximum health of the enemy
  float getMaxHealth() const;

  /// \brief Get the movement speed of the enemy
  /// \return Movement speed of the enemy
  int getMoveSpeed() const;

  /// \brief Get the bounty of the enemy
  /// \return Bounty of the enemy
  int getBounty() const;

  /// \brief Status of enemy armor
  /// \return True if the enemy is armored otherwise false
  bool isArmored() const;

  /// \brief Set the total distance moved on the path by the enemy
  void setDistanceMoved(float distance);

  /// \brief Get the distance enemy has travelled
  /// \return Distance the enemy has travelled
  float getDistanceMoved() const;

  /// \brief Set the slowed_level of the enemy
  void setSlowedLevel(unsigned int level);

  /// \brief Get the slowed level of the enemy
  /// \return slowed_level of the enemy
  unsigned int getSlowedLevel() const;

 protected:
  float health_;          ///< Remaining health of the enemy
  float max_health_;      ///< Maximum health of the enemy
  int move_speed_;        ///< Movement speed of the enemy
  int bounty_;            ///< Bounty of the enemy
  bool armored_;          ///< Status of enemy armor
  float distance_moved_;  ///< Total distance moved on the path by the enemy
  unsigned int slowed_level_;  ///< Level by witch the enemy is slowed
};
}  // namespace td
