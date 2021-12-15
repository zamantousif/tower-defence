#include "thorn_eruptor.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <optional>

#include "projectile.hpp"
#include "types.hpp"
#include "constants.hpp"
#include "enemy.hpp"

namespace td {
float hitbox_thorn = 28.0f;

unsigned int attack_speed_thorn = 120;  // can adjust these later

float range_thorn = 160.0f;

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

void ThornEruptor::Update(types::Time dt, std::list<Enemy>& enemies, std::list<Projectile>& projectiles) {
  time_since_last_shoot_ += dt;
  if (time_since_last_shoot_.asMilliseconds() >= attack_speed_*10) {
    bool tower_shot = ThornEruptor::Shoot(projectiles, enemies);

    if (tower_shot) {
      time_since_last_shoot_ = sf::seconds(0);
    }
  }
}

bool ThornEruptor::Shoot(
    std::list<Projectile>& projectiles, std::list<Enemy>& enemies) {
  int damage_thorn = 14;
  unsigned int enemy_pierced_count_thorn = 1;

  if (level_ == 2) {
    damage_thorn = 20;
  } else if (level_ == 3) {
    damage_thorn = 30;
  } else if (level_ == 4) {
    damage_thorn = 30;
  }

  std::vector<Enemy*> enemies_in_range;
  for (Enemy& enemy : enemies) {
    if (IsCircleCollidingWithCircle(position_, range_, enemy.getPosition(), enemy.getHitboxRadius())) {
      enemies_in_range.push_back(&enemy);
    }
  }
  if (enemies_in_range.size() == 0) return false;
  attack_speed_ = attack_speed_thorn/enemies_in_range.size();
  unsigned int random_index = std::rand() %  enemies_in_range.size();
  Enemy* target = enemies_in_range[random_index];
  
  rotation_angle_ = Angle2D(1, 0, target->getPosition().x - position_.x, target->getPosition().y - position_.y );
  Projectile new_projectile = Projectile(
  GetProjectStartPos(), 8.f, texture_projectile_, rotation_angle_, damage_thorn,
  false, enemy_pierced_count_thorn, 60.f, range_*1.2f);
  projectiles.push_back(new_projectile);
  if (level_ < 4 || enemies_in_range.size() == 1) {
    return true;
  }
  
  //level 4 shoots at two enemies
  unsigned int random_index2 = std::rand() %  enemies_in_range.size();
  while (random_index2 == random_index) {
    random_index2 = std::rand() %  enemies_in_range.size();
  }
  Enemy* target2 = enemies_in_range[random_index];
  
  rotation_angle_ = Angle2D(1, 0, target2->getPosition().x - position_.x, target2->getPosition().y - position_.y );
  Projectile new_projectile2 = Projectile(
  GetProjectStartPos(), 8.f, texture_projectile_, rotation_angle_, damage_thorn,
  false, enemy_pierced_count_thorn, 60.f, range_*1.2f);
  projectiles.push_back(new_projectile2);
  return true;
  
}

}  // namespace td