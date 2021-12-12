#include "slowing_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include "constants.hpp"

namespace td {
float hitbox_slowing = 30.0f;  // parameters radius and pointCount

unsigned int attack_speed_slowing = 10;  // can adjust these later

float range_slowing = 100.0f;

std::vector<unsigned int> upgrade_costs_slowing = {120, 140, 160};

Slowing_tower::Slowing_tower(sf::Vector2<float> position, float rotation_angle,
                             sf::Texture* texture)
    : Tower(position, hitbox_slowing, texture, nullptr, rotation_angle,
            attack_speed_slowing, range_slowing, kCostSlowingTower, 120) {}

std::list<Projectile> Slowing_tower::shoot(
    std::list<Projectile> projectiles,
    std::vector<Enemy> enemies) {
  /// NOTE! Before starting each frame or time segment the slowed_level_
  /// parameters of all enemies should be set to 0!
  float towerxpos = position_.x;
  float towerypos = position_.y;
  for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();
       it++) {
    float enemyxpos = (*it).getPosition().x;
    float enemyypos = (*it).getPosition().y;
    if (sqrt(pow(enemyxpos - towerxpos, 2) + pow(enemyypos - towerypos, 2)) <=
        range_ + (*it).getHitboxRadius()) {  // if enemy in tower range
      if ((*it).getSlowedLevel() < level_ && (*it).getBounty() != 400)
        (*it).setSlowedLevel(level_);
      /// if enemy is not in range of another slowing tower that has bigger
      /// level, set slowing_level to be same as level of this tower.
      /// (*it)->getBounty() != 400 makes dragonfly immune to slowring tower
    }
  }
  return projectiles;
}

}  // namespace td