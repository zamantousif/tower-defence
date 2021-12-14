#include "thorn_eruptor.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <optional>

#include "basic_projectile.hpp"
#include "projectile.hpp"
#include "types.hpp"
#include "constants.hpp"
#include "enemy.hpp"

namespace td {
float hitbox_thorn = 28.0f;

unsigned int attack_speed_thorn = 10;  // can adjust these later

float range_thorn = 130.0f;

ThornEruptor::ThornEruptor(types::Position position, float rotation_angle,
                         sf::Texture* texture, sf::Texture* texture_projectile)
    : Tower(position, hitbox_thorn, texture, texture_projectile, rotation_angle,
            attack_speed_thorn, range_thorn, kCostThornEruptor, 160, 1, types::kArea) {
              name_ = "thorn_eruptor";
            }

void ThornEruptor::Upgrade() {
  if (level_ == 1) {
    level_++;
    upgrade_cost_ = 210;
  } else if (level_ == 2) {
    level_++;
    range_ += 30;
    upgrade_cost_ = 300;
  } else if (level_ == 3) {
    level_++;
  }
}

bool ThornEruptor::shoot(
    std::list<Projectile> projectiles, std::vector<Enemy> enemies) {
  int damage_thorn = 14;
  unsigned int enemy_pierced_count_thorn = 1;

  if (level_ == 2) {
    damage_thorn = 20;
  } else if (level_ == 3) {
    damage_thorn = 30;
  } else if (level_ == 4) {
    damage_thorn = 30;
  }

  std::optional<const Enemy*> target = GetTarget(enemies);
  if (target) {
    rotation_angle_ = Angle2D(0, 1, target.value()->getPosition().x - position_.x, target.value()->getPosition().y - position_.y );
    Projectile new_projectile = Projectile(
    GetProjectStartPos(), 8.f, texture_projectile_, rotation_angle_, damage_thorn,
    false, enemy_pierced_count_thorn);
    projectiles.push_back(new_projectile);
  } else {
    return false;
  }
}

}  // namespace td