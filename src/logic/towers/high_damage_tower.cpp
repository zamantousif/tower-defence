#include "high_damage_tower.hpp"

#include <SFML/Graphics.hpp>

#include "massive_projectile.hpp"

namespace td {
float hitbox_high = 1.0f;

sf::Texture* texture_high = nullptr;  // picture of the tower to here

unsigned int attack_speed_high = 10;  // can adjust these later

float range_high = 10.0f;

char targetTo_high = 's';  // target strongest enemy

High_damage_tower::High_damage_tower(sf::Vector2<float> position,
                                     float rotation_angle)
    : Tower(position, hitbox_high, texture_high, rotation_angle,
            attack_speed_high, range_high, targetTo_high) {}

std::list<projectiles::Projectile> High_damage_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
  int damage_high = 0;
  if (this->getLevel() == 1)
    damage_high = 200;
  else if (this->getLevel() == 2)
    damage_high = 400;
  else if (this->getLevel() == 3)
    damage_high = 800;
  else
    damage_high = 1300;
  //    derived_projectile newProjectile =
  //    derived_projectile(this->getTarget(/*vector of enemies
  //    here*/)->getPosition(), this->getRotation(), damage_high); /// will
  //    create projectile straight on top of targeted enemy
  projectiles::Massive_projectile newProjectile =
      projectiles::Massive_projectile(
          GetProjectStartPos(this->getPosition(), this->getHitboxRadius(),
                             this->getRotation()),
          this->getRotation(),
          damage_high);  /// Projectile starts from the edge of the tower
  projectiles.push_back(newProjectile);
  return projectiles;
}

}  // namespace td