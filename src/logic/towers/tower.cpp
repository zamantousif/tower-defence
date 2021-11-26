#include "tower.hpp"

namespace td
{
    Tower::Tower(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float rotation_angle, unsigned int attack_speed, float range) : 
        Object(position, hitbox, sprite, rotation_angle), attack_speed_(attack_speed), range_(range) {}

    Tower::Tower(sf::Vector2<float> position, float rotation_angle, unsigned int attack_speed) : 
        Object(position, sf::CircleShape(1.0f, 30UL), sf::Texture(), rotation_angle), attack_speed_(attack_speed), range_(1.0) {}

    sf::Vector2<float> Tower::getPosition()
    {
        return position_;
    }

    sf::CircleShape Tower::getHitbox()
    {
        return hitbox_;
    }
    
    void Tower::setRotation(float angle)
    {
        rotation_angle_ = angle;
    }

    float Tower::getRotation()
    {
        return rotation_angle_;
    }

    unsigned int Tower::getAttackSpeed()
    {
        return attack_speed_;
    }

    float Tower::getRange()
    {
        return range_;
    }
}
