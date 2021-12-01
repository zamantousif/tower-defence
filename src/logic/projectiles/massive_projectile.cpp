#include <SFML/Graphics.hpp>
#include "massive_projectile.hpp"

namespace td::projectiles {
    sf::CircleShape hitbox_massive = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

    sf::Texture sprite_massive = sf::Texture();   //picture of the tower to here

    bool is_armor_piercing_massive = true;
        
    unsigned int enemy_pierced_count_massive = 1;

    Massive_projectile::Massive_projectile(sf::Vector2<float> position, float rotation_angle, int damage):
    Projectile(position, hitbox_massive, sprite_massive, rotation_angle, damage, is_armor_piercing_massive, enemy_pierced_count_massive) {}


}