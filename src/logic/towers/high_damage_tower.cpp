#include "high_damage_tower.hpp"

#include <SFML/Graphics.hpp>

#include "massive_projectile.hpp"
#include "constants.hpp"

namespace td {
float hitbox_high = 30.0f;

unsigned int attack_speed_high = 120;  // can adjust these later

float range_high = 500.0f;

types::Targeting targeting_high = types::kStrong;  // target strongest enemy

std::vector<unsigned int> upgrade_costs_high = {300, 350, 500};

High_damage_tower::High_damage_tower(sf::Vector2<float> position,
                                     float rotation_angle, sf::Texture* texture,
                                     sf::Texture* texture_projectile)
    : Tower(position, hitbox_high, texture, texture_projectile, rotation_angle,
            attack_speed_high, range_high, kCostHighDamageTower, 300, 1, targeting_high) {
              name_ = "sniper_tower";
            }

void High_damage_tower::Upgrade() {
  if (level_ == 1) {
    level_++;
    upgrade_cost_ = 350;
  } else if (level_ == 2) {
    level_++;
    attack_speed_ *= 0.8;
    upgrade_cost_ = 500;
  } else if (level_ == 3) {
    attack_speed_ *= 0.8;
    level_++;
  }
}

bool High_damage_tower::Shoot(
    std::list<Projectile>& projectiles, std::list<Enemy>& enemies) {
  int damage_high = 0;
  if (level_ == 1)
    damage_high = 200;
  else if (level_ == 2)
    damage_high = 400;
  else if (level_ == 3)
    damage_high = 800;
  else
    damage_high = 1300;

  std::optional<Enemy*> target = GetTarget(enemies);
  if (target) {
    return target.value()->TakeDamage(damage_high, true);
  } else {
    return false;
  }
}

}  // namespace td