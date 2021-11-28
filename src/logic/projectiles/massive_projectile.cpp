#include <SFML/Graphics.hpp>
#include "massive_projectile.hpp"

namespace td{
    sf::CircleShape hitbox5 = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

    sf::Texture sprite5 = sf::Texture();   //picture of the tower to here

    int damage5 = 200;

    bool is_armor_piercing5 = true;
        
    unsigned int enemy_pierced_count5 = 1;

    Massive_projectile::Massive_projectile(sf::Vector2<float> position, float rotation_angle):
    Projectile(position, hitbox5, sprite5, rotation_angle, damage5, is_armor_piercing5, enemy_pierced_count5) {}


}