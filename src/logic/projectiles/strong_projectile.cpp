#include "strong_projectile.hpp"
#include <SFML/Graphics.hpp>

namespace td{
    sf::CircleShape hitbox2 = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

    sf::Texture sprite2 = sf::Texture();   //picture of the tower to here

    int damage2 = 50;

    bool is_armor_piercing2 = false;
        
    unsigned int enemy_pierced_count2 = 3;

    Strong_projectile::Strong_projectile(sf::Vector2<float> position, float rotation_angle):
    Projectile(position, hitbox2, sprite2, rotation_angle, damage2, is_armor_piercing2, enemy_pierced_count2) {}


}