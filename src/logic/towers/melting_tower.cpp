#include "melting_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "constants.hpp"
#include "collision.hpp"

namespace td {
float hitbox_melting = 30.0f;

unsigned int attack_speed_melting = 20;

float range_melting = 120.0f;

Melting_tower::Melting_tower(sf::Vector2<float> position, float rotation_angle,
                             sf::Texture* texture)
    : Tower(position, hitbox_melting, texture, nullptr, rotation_angle,
            attack_speed_melting, range_melting, kCostMeltingTower, 100, 1, types::kArea) {
              name_ = "melting_tower";
            }

void Melting_tower::Upgrade() {
  if (level_ == 1) {
    level_++;
    upgrade_cost_ = 120;
  } else if (level_ == 2) {
    level_++;
    attack_speed_ *= 0.8;
    upgrade_cost_ = 170;
  } else if (level_ == 3) {
    level_++;
    range_ += 10;
  }
}

void Melting_tower::Update(types::Time dt, std::list<Enemy>& enemies, std::list<Projectile>& projectiles) {
  time_since_last_shoot_ += dt;
  if (time_since_last_shoot_.asMilliseconds() >= attack_speed_*10) {
    bool tower_shot = Melting_tower::Shoot(projectiles, enemies);

    if (tower_shot) {
      time_since_last_shoot_ = sf::seconds(0);
    }
  }
}

bool Melting_tower::Shoot(
    std::list<Projectile>& projectiles,
    std::list<Enemy>& enemies) {
      bool melting_armor_piercing = false;
      if (level_ == 4) {
        melting_armor_piercing = true;
      }
  for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end();
       it++) {
    if (IsCircleCollidingWithCircle(position_, range_, it->getPosition(), it->getHitboxRadius()/2)) {  // if enemy is in tower range
      it->TakeDamage(2.f * (1+level_), melting_armor_piercing);
    }
  }
  return true;
}

}  // namespace td