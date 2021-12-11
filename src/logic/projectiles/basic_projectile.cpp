#include "basic_projectile.hpp"

#include <SFML/Graphics.hpp>

namespace td {
float hitbox_basic = 1.0f;

bool is_armor_piercing_basic = false;

Basic_projectile::Basic_projectile(sf::Vector2<float> position,
                                   float rotation_angle, int damage,
                                   unsigned int enemy_pierced_count,
                                   sf::Texture* texture_projectile)
    : Projectile(position, hitbox_basic, texture_projectile , rotation_angle, damage,
                 is_armor_piercing_basic, enemy_pierced_count) {}

//void Basic_projectile::Update(td::types::Time dt) { (void)dt; }

}  // namespace td::projectiles