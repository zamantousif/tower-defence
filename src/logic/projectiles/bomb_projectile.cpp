#include "bomb_projectile.hpp"

#include <SFML/Graphics.hpp>

namespace td {
float hitbox_bomb_projectile = 10.0f;

bool is_armor_piercing_bomb = true;

unsigned int enemy_pierced_count_bomb = 1;

Bomb_projectile::Bomb_projectile(sf::Vector2<float> position,
                                 float rotation_angle, int damage,
                                 sf::Texture* texture_projectile, sf::Texture* texture_explosion)
    : Projectile(position, hitbox_bomb_projectile, texture_projectile, rotation_angle, damage,
                 is_armor_piercing_bomb, enemy_pierced_count_bomb) {
                   texture_explosion_ = texture_explosion;
                 }

}  // namespace td