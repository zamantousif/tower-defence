#include "melting_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include "constants.hpp"
#include "collision.hpp"

namespace td {
float hitbox_melting = 30.0f;  // parameters radius and pointCount

unsigned int attack_speed_melting = 10;  // can adjust these later

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

bool Melting_tower::Shoot(
    std::list<Projectile>& projectiles,
    std::list<Enemy>& enemies) {
      bool melting_armor_piercing = false;
      if (level_ == 4) {
        melting_armor_piercing = true;
      }
  for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end();
       it++) {
    if (IsCircleCollidingWithCircle(position_, range_, it->getPosition(), it->getHitboxRadius())) {  // if enemy is in tower range
      it->TakeDamage(3.f * level_, melting_armor_piercing);
    }
  }
  return true;
}

}  // namespace td