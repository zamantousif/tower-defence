#include "bomb_tower.hpp"

#include <SFML/Graphics.hpp>

#include "bomb_projectile.hpp"

namespace td {
float hitbox_bomb = 1.0f;

unsigned int attack_speed_bomb = 10;  // can adjust these later

float range_bomb = 10.0f;

Bomb_tower::Bomb_tower(sf::Vector2<float> position, float rotation_angle,
                       sf::Texture* texture, sf::Texture* texture_projectile)
    : Tower(position, hitbox_bomb, texture, texture_projectile, rotation_angle,
            attack_speed_bomb, range_bomb) {}

std::list<projectiles::Projectile> Bomb_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
  int damage_bomb = 0;
  if (this->getLevel() == 1)
    damage_bomb = 15;
  else if (this->getLevel() == 2)
    damage_bomb = 30;
  else if (this->getLevel() == 3)
    damage_bomb = 45;
  else
    damage_bomb = 60;
  projectiles::Bomb_projectile newProjectile = projectiles::Bomb_projectile(
      GetProjectStartPos(this->getPosition(), this->getHitboxRadius(),
                         this->getRotation()),
      this->getRotation(),
      damage_bomb, texture_projectile_);  /// Projectile starts from the edge of the tower
  projectiles.push_back(newProjectile);
  return projectiles;
}

}  // namespace td