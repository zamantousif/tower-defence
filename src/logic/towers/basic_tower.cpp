#include "basic_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

#include "basic_projectile.hpp"
#include "projectile.hpp"
#include "types.hpp"

namespace td {
float hitbox_basic_tower = 30.0f;

unsigned int attack_speed_basic = 10;  // can adjust these later

float range_basic = 10.0f;

std::vector<unsigned int> upgrade_costs_basic = { 80, 80, 200 };

unsigned int Basic_tower::getUpgradeCost()
{
  return upgrade_costs_basic.at(level_-1);
}

Basic_tower::Basic_tower(types::Position position, float rotation_angle,
                         sf::Texture* texture, sf::Texture* texture_projectile)
    : Tower(position, hitbox_basic_tower, texture, texture_projectile, rotation_angle,
            attack_speed_basic, range_basic) {}

std::list<Projectile> Basic_tower::shoot(
    std::list<Projectile> projectiles, std::vector<Enemy> enemies) {
  int damage_basic = 0;
  unsigned int enemy_pierced_count_basic = 1;
  if (level_ == 1)
    damage_basic = 10;
  else if (level_ == 2)
    damage_basic = 20;
  else if (level_ == 3)
    damage_basic = 30;
  else if (level_ == 4) {
    damage_basic = 50;
    enemy_pierced_count_basic = 3;
  }
  Basic_projectile newProjectile = Basic_projectile(
      GetProjectStartPos(), rotation_angle_, damage_basic,
      enemy_pierced_count_basic,
      texture_projectile_);  /// Projectile starts from the edge of the tower
  projectiles.push_back(newProjectile);
  return projectiles;
}

}  // namespace td