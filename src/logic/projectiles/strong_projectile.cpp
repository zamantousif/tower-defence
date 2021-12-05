#include "strong_projectile.hpp"

#include <SFML/Graphics.hpp>


namespace td::projectiles {
float hitbox_strong = 1.0f; 

sf::Texture* texture_strong = nullptr;  // picture of the projectile to here

int damage_strong = 50;

bool is_armor_piercing_strong = false;

unsigned int enemy_pierced_count_strong = 3;

Strong_projectile::Strong_projectile(sf::Vector2<float> position,
                                     float rotation_angle)
    : Projectile(position, hitbox_strong, texture_strong, rotation_angle,
                 damage_strong, is_armor_piercing_strong,
                 enemy_pierced_count_strong) {}

}  // namespace td::projectiles