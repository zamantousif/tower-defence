#include "projectile.hpp"

namespace td
{
    Projectile::Projectile(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float rotation_angle, float damage, 
    bool is_armor_piercing, unsigned int enemy_pierced_count) : Object(position, hitbox, sprite, rotation_angle), damage_(damage), 
        is_armor_piercing_(is_armor_piercing), enemy_pierced_count_(enemy_pierced_count), exhausted_(false) {}

    float Projectile::getDamage() const
    {
        return damage_;
    }

    bool Projectile::isArmorPiercing() const
    {
        return is_armor_piercing_;
    }

    unsigned int Projectile::getEnemyPiercedCount() const
    {
        return enemy_pierced_count_;
    }

    bool Projectile::isExhausted() const
    {
      return exhausted_;
    }

}
