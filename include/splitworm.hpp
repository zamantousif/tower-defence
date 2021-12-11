#pragma once

#include <SFML/Graphics.hpp>

#include "enemy.hpp"

namespace td {
///  \brief //Implementation of splitworm
class Splitworm : public Enemy {
 public:
  /// \brief                Splitworm constructor
  /// \param position       Position of the enemy
  /// \param hitbox         Radius of the circular region occupied by the enemy
  /// \param texture        A pointer to the texture of the enemy
  /// \param health         Health of the enemy
  /// \param move_speed     Movement speed of the enemy
  /// \param bounty         Bounty of the enemy
  /// \param armored        Status ofenemy armor
  /// \param moved_distance Total distance moved on the path by the enemy
  Splitworm(types::Position startOfTheMap, float hitbox, sf::Texture* texture,
            float health = 150, int move_speed = 20, float bounty = 0.0f,
            bool armored = true, float distance_moved = 0.0f);


  /// \brief           Splitworm creates 3 weaker worm upon death
  /// \param texture   Texture of the weaker worm     
  std::vector<Enemy> doUponDeath(sf::Texture* texture);

};
}  // namespace td
