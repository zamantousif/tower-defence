#include "high_damage_tower.hpp"

#include <SFML/Graphics.hpp>

#include "massive_projectile.hpp"
#include "constants.hpp"

namespace td {
float hitbox_high = 30.0f;

unsigned int attack_speed_high = 10;  // can adjust these later

float range_high = 450.0f;

char targeting_high = types::kStrong;  // target strongest enemy

std::vector<unsigned int> upgrade_costs_high = {300, 350, 500};

High_damage_tower::High_damage_tower(sf::Vector2<float> position,
                                     float rotation_angle, sf::Texture* texture,
                                     sf::Texture* texture_projectile)
    : Tower(position, hitbox_high, texture, texture_projectile, rotation_angle,
            attack_speed_high, range_high, kCostHighDamageTower, 300, targeting_high) {}

std::list<Projectile> High_damage_tower::shoot(
    std::list<Projectile> projectiles, std::vector<Enemy> enemies) {
  int damage_high = 0;
  if (level_ == 1)
    damage_high = 200;
  else if (level_ == 2)
    damage_high = 400;
  else if (level_ == 3)
    damage_high = 800;
  else
    damage_high = 1300;
  //    derived_projectile newProjectile =
  //    derived_projectile(this->getTarget(/*vector of enemies
  //    here*/)->getPosition(), this->getRotation(), damage_high); /// will
  //    create projectile straight on top of targeted enemy
  Massive_projectile newProjectile =
      Massive_projectile(GetProjectStartPos(), rotation_angle_, damage_high,
                         texture_projectile_);  /// Projectile starts from the
                                                /// edge of the tower
  projectiles.push_back(newProjectile);
  return projectiles;
}

}  // namespace td