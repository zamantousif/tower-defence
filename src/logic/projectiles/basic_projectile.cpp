#include "basic_projectile.hpp"
#include <SFML/Graphics.hpp>

namespace td::projectiles{
    sf::CircleShape hitbox1 = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

    sf::Texture sprite1 = sf::Texture();   //picture of the tower to here

    bool is_armor_piercing1 = false;
        
    unsigned int enemy_pierced_count1 = 1;

    Basic_projectile::Basic_projectile(sf::Vector2<float> position, float rotation_angle, int damage):
    Projectile(position, hitbox1, sprite1, rotation_angle, damage, is_armor_piercing1, enemy_pierced_count1) {}


}