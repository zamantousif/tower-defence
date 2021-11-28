#include "strong_projectile.hpp"
#include <SFML/Graphics.hpp>

namespace td{
    sf::CircleShape hitbox = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

    sf::Texture sprite = sf::Texture();   //picture of the tower to here

    int damage = 10;

    bool is_armor_piercing = false;
        
    unsigned int enemy_pierced_count = 3;

    Strong_projectile::Strong_projectile(sf::Vector2<float> position, float rotation_angle):
    Projectile(position, hitbox, sprite, rotation_angle, damage, is_armor_piercing, enemy_pierced_count) {}


}