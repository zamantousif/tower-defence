#include "basic_projectile.hpp"

#include <SFML/Graphics.hpp>


namespace td::projectiles {
float hitbox_basic = 1.0f; 

sf::Texture* texture_basic = nullptr;  // picture of the projectile to here

bool is_armor_piercing_basic = false;

unsigned int enemy_pierced_count_basic = 1;

Basic_projectile::Basic_projectile(sf::Vector2<float> position,
                                   float rotation_angle, int damage)
    : Projectile(position, hitbox_basic, texture_basic, rotation_angle, damage,
                 is_armor_piercing_basic, enemy_pierced_count_basic) {}

void Basic_projectile::Update(td::types::Time dt)
{ (void)dt; }

}  // namespace td::projectiles