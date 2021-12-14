#include "basic_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <optional>

#include "basic_projectile.hpp"
#include "projectile.hpp"
#include "types.hpp"
#include "constants.hpp"
#include "enemy.hpp"

namespace td {
float hitbox_basic_tower = 27.0f;

unsigned int attack_speed_basic = 10;  // can adjust these later

float range_basic = 150.0f;

Basic_tower::Basic_tower(types::Position position, float rotation_angle,
                         sf::Texture* texture, sf::Texture* texture_projectile)
    : Tower(position, hitbox_basic_tower, texture, texture_projectile, rotation_angle,
            attack_speed_basic, range_basic, kCostBasicTower, 90) {
              name_ = "basic_tower";
            }

void Basic_tower::Upgrade() {
  if (level_ == 1) {
    level_++;
    upgrade_cost_ = 140;
  } else if (level_ == 2) {
    level_++;
    range_ += 30;
    upgrade_cost_ = 200;
  } else if (level_ == 3) {
    level_++;
    range_ += 10;
  }
}

bool Basic_tower::Shoot(
    std::list<Projectile>& projectiles, std::list<Enemy>& enemies) {
  int damage_basic = 10;
  unsigned int enemy_pierced_count_basic = 1;

  if (level_ == 2) {
    damage_basic = 20;
  } else if (level_ == 3) {
    damage_basic = 30;
    enemy_pierced_count_basic = 2;
  } else if (level_ == 4) {
    enemy_pierced_count_basic = 2;
    damage_basic = 30;
  }

  std::optional<Enemy*> target = GetTarget(enemies);
  if (target) {
    rotation_angle_ = Angle2D(0, 1, target.value()->getPosition().x - position_.x, target.value()->getPosition().y - position_.y );
    Projectile new_projectile = Projectile(
    GetProjectStartPos(), 8.f, texture_projectile_, rotation_angle_, damage_basic,
    false, enemy_pierced_count_basic);
    projectiles.push_back(new_projectile);

    if (level_ >= 4) {
    Projectile new_projectile_left = Projectile(
    GetProjectStartPos(), 8.f, texture_projectile_, rotation_angle_+0.5f, damage_basic,
    false, enemy_pierced_count_basic);
    Projectile new_projectile_right = Projectile(
    GetProjectStartPos(), 8.f, texture_projectile_, rotation_angle_-0.5f, damage_basic,
    false, enemy_pierced_count_basic);
    projectiles.push_back(new_projectile_left);
    projectiles.push_back(new_projectile_right);
    }

    return true;
  } else {
    return false;
  }
}

}  // namespace td