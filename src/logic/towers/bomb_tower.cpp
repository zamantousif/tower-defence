#include "bomb_tower.hpp"

#include <SFML/Graphics.hpp>

#include "bomb_projectile.hpp"
#include "constants.hpp"

namespace td {
float hitbox_bomb_tower = 32.0f;

unsigned int attack_speed_bomb = 200;  // can adjust these later

float range_bomb = 150.0f;

Bomb_tower::Bomb_tower(sf::Vector2<float> position, float rotation_angle,
                       sf::Texture* texture, sf::Texture* texture_projectile,
                       sf::Texture* texture_explosion)
    : Tower(position, hitbox_bomb_tower, texture, texture_projectile, rotation_angle,
            attack_speed_bomb, range_bomb, kCostBombTower, 140) {
              name_ = "bomb_tower";
              texture_explosion_ = texture_explosion;
            }

void Bomb_tower::Upgrade() {
  if (level_ == 1) {
    level_++;
    upgrade_cost_ = 140;
    range_ += 20;
  } else if (level_ == 2) {
    level_++;
    attack_speed_ *= 0.8;
    upgrade_cost_ = 300;
  } else if (level_ == 3) {
    level_++;
  }
}

void Bomb_tower::Update(types::Time dt, std::list<Enemy>& enemies, std::list<Projectile>& projectiles) {
  time_since_last_shoot_ += dt;
  if (time_since_last_shoot_.asMilliseconds() >= attack_speed_*10) {
    bool tower_shot = Bomb_tower::Shoot(projectiles, enemies);

    if (tower_shot) {
      time_since_last_shoot_ = sf::seconds(0);
    }
  }
}

bool Bomb_tower::Shoot(
    std::list<Projectile>& projectiles, std::list<Enemy>& enemies) {
  int damage_bomb = 0;
  float explosion_radius = 40;
  if (level_ == 1)
    damage_bomb = 20;
  else if (level_ == 2)
    damage_bomb = 30;
  else if (level_ == 3)
    damage_bomb = 45;
  else {
    damage_bomb = 60;
    explosion_radius = 80;
  }
    
  std::optional<Enemy*> target = GetTarget(enemies);
  if (target) {
    rotation_angle_ = Angle2D(1, 0, target.value()->getPosition().x - position_.x, target.value()->getPosition().y - position_.y );
    Bomb_projectile new_projectile = Bomb_projectile(
    GetProjectStartPos(), rotation_angle_, damage_bomb,
      texture_projectile_, texture_explosion_);
    projectiles.push_back(new_projectile);
    return true;
  } else {
    return false;
  }
}

}  // namespace td