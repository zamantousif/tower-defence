#include "Tower.hpp"

namespace td
{
    Tower::Tower(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, unsigned int attackSpeed, float range) : 
        Object(position, hitbox, sprite), attackSpeed_(attackSpeed), range_(range) {}

    Tower::Tower(sf::Vector2<float> position, unsigned int attackSpeed) : 
        Object(position, sf::CircleShape(1.0f, 30UL), sf::Texture()), attackSpeed_(attackSpeed), range_(1.0) {}

    sf::Vector2<float> Tower::getPosition()
    {
        return position_;
    }

    sf::CircleShape Tower::getHitbox()
    {
        return hitbox_;
    }

    unsigned int Tower::getAttackSpeed()
    {
        return attackSpeed_;
    }

    float Tower::getRange()
    {
        return range_;
    }

}
