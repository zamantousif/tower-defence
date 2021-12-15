#include "slowing_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include "constants.hpp"
#include "collision.hpp"

namespace td {
float hitbox_slowing = 30.0f;  // parameters radius and pointCount

unsigned int attack_speed_slowing = 0;  // can adjust these later

float range_slowing = 120.0f;

std::vector<unsigned int> upgrade_costs_slowing = {120, 140, 160};

Slowing_tower::Slowing_tower(sf::Vector2<float> position, float rotation_angle,
                             sf::Texture* texture)
    : Tower(position, hitbox_slowing, texture, nullptr, rotation_angle,
            attack_speed_slowing, range_slowing, kCostSlowingTower, 120, 1, types::kArea) {
              name_ = "slowing_tower";
            }

void Slowing_tower::Upgrade() {
  if (level_ == 1) {
    level_++;
    upgrade_cost_ = 140;
  } else if (level_ == 2) {
    level_++;
    attack_speed_ *= 0.8;
    upgrade_cost_ = 160;
  } else if (level_ == 3) {
    level_++;
    range_ += 10;
  }
}

void Slowing_tower::Update(types::Time dt, std::list<Enemy>& enemies, std::list<Projectile>& projectiles) {
  time_since_last_shoot_ += dt;
  if (time_since_last_shoot_.asMilliseconds() >= attack_speed_*10) {
    bool tower_shot = Slowing_tower::Shoot(projectiles, enemies);

    if (tower_shot) {
      time_since_last_shoot_ = sf::seconds(0);
    }
  }
}

bool Slowing_tower::Shoot(
    std::list<Projectile>& projectiles,
    std::list<Enemy>& enemies) {
  /// NOTE! Before starting each frame or time segment the slowed_level_
  /// parameters of all enemies should be set to 0!
  for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end();
       it++) {
    if (IsCircleCollidingWithCircle(position_, range_, it->getPosition(), it->getHitboxRadius()/2)) {  // if enemy in tower range
      /// if enemy is not in range of another slowing tower that has bigger
      /// level, set slowing_level to be same as level of this tower.
      /// it->getBounty() != 400 makes dragonfly immune to slowring tower
      if (it->getSlowedLevel() < level_ && it->getBounty() != 400) {
        it->setSlowedLevel(level_);
      }
    }
  }
  return true;
}

}  // namespace td