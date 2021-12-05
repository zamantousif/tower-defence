#include "basic_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

#include "basic_projectile.hpp"
#include "projectile.hpp"
#include "strong_projectile.hpp"
#include "types.hpp"


namespace td {
float hitbox_basic = 1.0f; 

sf::Texture* texture_basic = nullptr;  // picture of the tower to here

unsigned int attack_speed_basic = 10;  // can adjust these later

float range_basic = 10.0f;

Basic_tower::Basic_tower(types::Position position, float rotation_angle)
    : Tower(position, hitbox_basic, texture_basic, rotation_angle,
            attack_speed_basic, range_basic) {}

int damage_basic = 0;
std::list<projectiles::Projectile> Basic_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
  if (this->getLevel() < 4) {
    if(this->getLevel() == 1)
    damage_basic = 10;
    else if(this->getLevel() == 2)
    damage_basic = 20;
    else if(this->getLevel() == 3)
    damage_basic = 30;
    projectiles::Basic_projectile newProjectile = projectiles::Basic_projectile(
        GetProjectStartPos(this->getPosition(), this->getHitbox(),
                           this->getRotation()),
        this->getRotation(),
        damage_basic);  /// Projectile starts from the edge of the tower
    projectiles.push_back(newProjectile);
    return projectiles;
  }else {
    projectiles::Strong_projectile newProjectile =
        projectiles::Strong_projectile(
            GetProjectStartPos(this->getPosition(), this->getHitbox(),
                               this->getRotation()),
            this->getRotation());
    projectiles.push_back(newProjectile);
    return projectiles;
  }
}

}  // namespace td