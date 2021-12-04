#include "basic_projectile.hpp"

#include <SFML/Graphics.hpp>


namespace td::projectiles {
float hitbox_basic = 1.0f;  // parameters radius and pointCount

sf::Texture sprite_basic = sf::Texture();  // picture of the tower to here

bool is_armor_piercing_basic = false;

unsigned int enemy_pierced_count_basic = 1;

Basic_projectile::Basic_projectile(sf::Vector2<float> position,
                                   float rotation_angle, int damage)
    : Projectile(position, hitbox_basic, sprite_basic, rotation_angle, damage,
                 is_armor_piercing_basic, enemy_pierced_count_basic) {}

}  // namespace td::projectiles