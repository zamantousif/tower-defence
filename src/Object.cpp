#include "Object.hpp"

namespace td
{
    Object::Object(sf::Vector2<unsigned int> position, sf::CircleShape hitbox, sf::Texture sprite) : 
        position_(position), hitbox_(hitbox), sprite_(sprite) {}

    sf::Vector2<unsigned int> Object::getPosition()
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

}
    
