#include "bomb_tower.hpp"

#include <SFML/Graphics.hpp>

#include "bomb_projectile.hpp"
#include "constants.hpp"

namespace td {
float hitbox_bomb_tower = 32.0f;

unsigned int attack_speed_bomb = 10;  // can adjust these later

float range_bomb = 150.0f;

Bomb_tower::Bomb_tower(sf::Vector2<float> position, float rotation_angle,
                       sf::Texture* texture, sf::Texture* texture_projectile)
    : Tower(position, hitbox_bomb_tower, texture, texture_projectile, rotation_angle,
            attack_speed_bomb, range_bomb, kCostBombTower, 140) {
              name_ = "bomb_tower";
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

std::list<Projectile> Bomb_tower::shoot(
    std::list<Projectile> projectiles, std::vector<Enemy> enemies) {
  int damage_bomb = 0;
  if (level_ == 1)
    damage_bomb = 20;
  else if (level_ == 2)
    damage_bomb = 30;
  else if (level_ == 3)
    damage_bomb = 45;
  else
    damage_bomb = 60;
  Bomb_projectile newProjectile = Bomb_projectile(
      GetProjectStartPos(), rotation_angle_, damage_bomb,
      texture_projectile_);  /// Projectile starts from the edge of the tower
  projectiles.push_back(newProjectile);
  return projectiles;
}

}  // namespace td