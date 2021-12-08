#include <SFML/Graphics.hpp>

#include "splitworm.hpp"

namespace td {
  Splitworm::Splitworm(types::Position startOfTheMap, float hitbox,
                       sf::Texture* texture, float health,
                       int move_speed, float bounty,
                       bool armored, float distance_moved)
      : Enemy(startOfTheMap, hitbox, texture, health, move_speed, bounty, armored,
              distance_moved){};

  std::vector<Enemy*> Splitworm::doUponDeath(sf::Texture* texture) {
    Enemy* weaker_worm =
        new Enemy(position_, 1.0f, texture, 50, 10, 10, false, distance_moved_);
    std::vector<Enemy*> weaker_worms;
    weaker_worms.push_back(weaker_worm);
    weaker_worms.push_back(weaker_worm);
    weaker_worms.push_back(weaker_worm);
    return weaker_worms;
  }
}  // namespace td