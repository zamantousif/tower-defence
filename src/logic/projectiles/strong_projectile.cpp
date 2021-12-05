#include "strong_projectile.hpp"

#include <SFML/Graphics.hpp>


namespace td::projectiles {
float hitbox_strong = 1.0f;  // parameters radius and pointCount

sf::Texture* sprite_strong = nullptr;  // picture of the tower to here

int damage_strong = 50;

bool is_armor_piercing_strong = false;

unsigned int enemy_pierced_count_strong = 3;

Strong_projectile::Strong_projectile(sf::Vector2<float> position,
                                     float rotation_angle)
    : Projectile(position, hitbox_strong, sprite_strong, rotation_angle,
                 damage_strong, is_armor_piercing_strong,
                 enemy_pierced_count_strong) {}

}  // namespace td::projectiles