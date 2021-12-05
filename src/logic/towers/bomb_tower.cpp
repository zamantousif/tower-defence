#include "bomb_tower.hpp"

#include <SFML/Graphics.hpp>

#include "bomb_projectile.hpp"


namespace td {
float hitbox_bomb = 1.0f; 

sf::Texture* sprite_bomb = nullptr;  // picture of the tower to here

unsigned int attack_speed_bomb = 10;  // can adjust these later

float range_bomb = 10.0f;

Bomb_tower::Bomb_tower(sf::Vector2<float> position, float rotation_angle)
    : Tower(position, hitbox_bomb, sprite_bomb, rotation_angle,
            attack_speed_bomb, range_bomb) {}

std::list<projectiles::Projectile> Bomb_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
      int damage_bomb = 0;
  if (this->getLevel() == 1)
    damage_bomb = 15;
    else if(this->getLevel() == 2)
    damage_bomb = 30;
    else if(this->getLevel() == 3)
    damage_bomb = 45;
    else
    damage_bomb = 60;
    projectiles::Bomb_projectile newProjectile =
        projectiles::Bomb_projectile(GetProjectStartPos(this->getPosition(), this->getHitbox(),
                               this->getRotation()), this->getRotation(),
                                     damage_bomb);  /// Projectile starts from the edge of the tower
    projectiles.push_back(newProjectile);
    return projectiles;
}

}  // namespace td