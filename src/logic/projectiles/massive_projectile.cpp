#include "massive_projectile.hpp"

#include <SFML/Graphics.hpp>


namespace td::projectiles {
float hitbox_massive = 1.0f;  

bool is_armor_piercing_massive = true;

unsigned int enemy_pierced_count_massive = 1;

Massive_projectile::Massive_projectile(sf::Vector2<float> position,
                                       float rotation_angle, int damage, sf::Texture* texture_projectile)
    : Projectile(position, hitbox_massive, texture_projectile, rotation_angle,
                 damage, is_armor_piercing_massive,
                 enemy_pierced_count_massive) {}

void Massive_projectile::Update(td::types::Time dt)
{ (void)dt; }

}  // namespace td::projectiles