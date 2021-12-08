#include "melting_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

namespace td {
float hitbox_melting = 1.0f;  // parameters radius and pointCount

unsigned int attack_speed_melting = 10;  // can adjust these later

float range_melting = 10.0f;

std::vector<unsigned int> upgrade_costs_melting = {100, 100, 150};

unsigned int Melting_tower::getUpgradeCost() {
  return upgrade_costs_melting.at(level_ - 1);
}

Melting_tower::Melting_tower(sf::Vector2<float> position, float rotation_angle,
                             sf::Texture* texture)
    : Tower(position, hitbox_melting, texture, nullptr, rotation_angle,
            attack_speed_melting, range_melting) {}

std::list<projectiles::Projectile> Melting_tower::shoot(
    std::list<projectiles::Projectile> projectiles,
    std::vector<Enemy*> enemies) {
  /// NOTE! Before starting each frame or time segment the melting_level_
  /// parameters of all enemies should be set to 0!
  float towerxpos = position_.x;
  float towerypos = position_.y;
  for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end();
       it++) {
    float enemyxpos = (*it)->getPosition().x;
    float enemyypos = (*it)->getPosition().y;
    if (sqrt(pow(enemyxpos - towerxpos, 2) + pow(enemyypos - towerypos, 2)) <=
        range_ + (*it)->getHitboxRadius()) {  // if enemy in tower range
      if ((*it)->getMeltingLevel() < level_) (*it)->setMeltingLevel(level_);
      /// if enemy is not in range of another melting tower that has bigger
      /// level, set melting_level to be same as level of this tower.
    }
  }
  return projectiles;
}

}  // namespace td