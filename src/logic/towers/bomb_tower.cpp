#include "bomb_tower.hpp"

#include <SFML/Graphics.hpp>

#include "bomb_projectile.hpp"

namespace td {
float hitbox_bomb = 1.0f;

unsigned int attack_speed_bomb = 10;  // can adjust these later

float range_bomb = 10.0f;

std::vector<unsigned int> upgrade_costs_bomb = { 140, 140, 300 };

unsigned int Bomb_tower::getUpgradeCost()
{
  return upgrade_costs_bomb.at(level_-1);
}

Bomb_tower::Bomb_tower(sf::Vector2<float> position, float rotation_angle,
                       sf::Texture* texture, sf::Texture* texture_projectile)
    : Tower(position, hitbox_bomb, texture, texture_projectile, rotation_angle,
            attack_speed_bomb, range_bomb) {}

std::list<projectiles::Projectile> Bomb_tower::shoot(
    std::list<projectiles::Projectile> projectiles, std::vector<Enemy> enemies) {
  int damage_bomb = 0;
  if (level_ == 1)
    damage_bomb = 15;
  else if (level_ == 2)
    damage_bomb = 30;
  else if (level_ == 3)
    damage_bomb = 45;
  else
    damage_bomb = 60;
  projectiles::Bomb_projectile newProjectile = projectiles::Bomb_projectile(
      GetProjectStartPos(), rotation_angle_, damage_bomb,
      texture_projectile_);  /// Projectile starts from the edge of the tower
  projectiles.push_back(newProjectile);
  return projectiles;
}

}  // namespace td