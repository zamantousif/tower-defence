#include "melting_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include "constants.hpp"

namespace td {
float hitbox_melting = 30.0f;  // parameters radius and pointCount

unsigned int attack_speed_melting = 10;  // can adjust these later

float range_melting = 100.0f;

Melting_tower::Melting_tower(sf::Vector2<float> position, float rotation_angle,
                             sf::Texture* texture)
    : Tower(position, hitbox_melting, texture, nullptr, rotation_angle,
            attack_speed_melting, range_melting, kCostMeltingTower, 100) {}

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

std::list<Projectile> Melting_tower::shoot(
    std::list<Projectile> projectiles,
    std::vector<Enemy> enemies) {
  float towerxpos = position_.x;
  float towerypos = position_.y;
  for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();
       it++) {
    float enemyxpos = (*it).getPosition().x;
    float enemyypos = (*it).getPosition().y;
    if (sqrt(pow(enemyxpos - towerxpos, 2) + pow(enemyypos - towerypos, 2)) <=
        range_ + (*it).getHitboxRadius()) {  // if enemy is in tower range
      (*it).setHealth(0.01 * level_);  //decrease 0.01*tower_level every frame
    }}
    return projectiles;
  }

}  // namespace td