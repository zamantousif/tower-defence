#include <SFML/Graphics.hpp>
#include "bomb_projectile.hpp"

namespace td::projectiles {
    sf::CircleShape hitbox6 = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

    sf::Texture sprite6 = sf::Texture();   //picture of the tower to here

    bool is_armor_piercing6 = true;
        
    unsigned int enemy_pierced_count6 = 1;

    Bomb_projectile::Bomb_projectile(sf::Vector2<float> position, float rotation_angle, int damage):
    Projectile(position, hitbox6, sprite6, rotation_angle, damage, is_armor_piercing6, enemy_pierced_count6) {}


}