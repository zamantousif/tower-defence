#include "basic_tower.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

#include "basic_projectile.hpp"
#include "projectile.hpp"
#include "types.hpp"


namespace td {
float hitbox_basic = 1.0f; 

unsigned int attack_speed_basic = 10;  // can adjust these later

float range_basic = 10.0f;

Basic_tower::Basic_tower(types::Position position, float rotation_angle, sf::Texture* texture, sf::Texture* texture_projectile)
    : Tower(position, hitbox_basic, texture, texture_projectile, rotation_angle,
            attack_speed_basic, range_basic) {}

std::list<projectiles::Projectile> Basic_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
      int damage_basic = 0;
      unsigned int enemy_pierced_count_basic = 1;
    if(this->getLevel() == 1)
    damage_basic = 10;
    else if(this->getLevel() == 2)
    damage_basic = 20;
    else if(this->getLevel() == 3)
    damage_basic = 30;
    else if(this->getLevel() == 4){
      damage_basic = 50;
      enemy_pierced_count_basic = 3;
    }
    projectiles::Basic_projectile newProjectile = projectiles::Basic_projectile(
        GetProjectStartPos(this->getPosition(), this->getHitboxRadius(),
                           this->getRotation()),
        this->getRotation(),
        damage_basic, enemy_pierced_count_basic, texture_projectile_);  /// Projectile starts from the edge of the tower
    projectiles.push_back(newProjectile);
    return projectiles;
}

}  // namespace td