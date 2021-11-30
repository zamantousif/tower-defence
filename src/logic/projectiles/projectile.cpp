#include "projectile.hpp"

namespace td
{
    Projectile::Projectile(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float rotation_angle, unsigned int damage, 
    bool is_armor_piercing, unsigned int enemy_pierced_count) : Object(position, hitbox, sprite, rotation_angle), damage_(damage), 
        is_armor_piercing_(is_armor_piercing), enemy_pierced_count_(enemy_pierced_count) {}
    
    sf::Vector2<float> Projectile::getPosition() const
    {
        return position_;
    }

    void Projectile::setRotation(float angle)
    {
        rotation_angle_ = angle;
    }

    float Projectile::getRotation() const
    {
        return rotation_angle_;
    }

    unsigned int Projectile::getDamage() const
    {
        return damage_;
    }

    bool Projectile::isArmorPiercing() const
    {
        return is_armor_piercing_;
    }

    void Projectile::setEnemyPiercedCount(unsigned int count)
    {
        enemy_pierced_count_ = count;
    }

    unsigned int Projectile::getEnemyPiercedCount() const
    {
        return enemy_pierced_count_;
    }

}
