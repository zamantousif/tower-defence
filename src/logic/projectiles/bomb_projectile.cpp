#include <SFML/Graphics.hpp>
#include "bomb_projectile.hpp"

namespace td::projectiles {
    float hitbox_bomb = 1.0f; //parameters radius and pointCount

    sf::Texture sprite_bomb = sf::Texture();   //picture of the tower to here

    bool is_armor_piercing_bomb = true;
        
    unsigned int enemy_pierced_count_bomb = 1;

    Bomb_projectile::Bomb_projectile(sf::Vector2<float> position, float rotation_angle, int damage):
    Projectile(position, hitbox_bomb, sprite_bomb, rotation_angle, damage, is_armor_piercing_bomb, enemy_pierced_count_bomb) {}


}