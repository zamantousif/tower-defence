#include "object.hpp"

namespace td
{
    Object::Object(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float rotation_angle) : 
        position_(position), hitbox_(hitbox), sprite_(sprite), rotation_angle_(rotation_angle) {}

    sf::Vector2<float> Object::getPosition()
    {
        return position_;
    }

    sf::CircleShape Object::getHitbox()
    {
        return hitbox_;
    }
    
    sf::Texture Object::getSprite()
    {
        return sprite_;
    }

    void Object::setPosition(sf::Vector2<float> position)
    {
        position_ = position;
    }

    void Object::setRotation(float angle)
    {
        rotation_angle_ = angle;
    }

    float Object::getRotation()
    {
        return rotation_angle_;
    }
}
    
