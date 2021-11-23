#pragma once

#include <SFML/Graphics.hpp>

namespace td
{
    /*  Object class is an abstract class representing the basic entity of the game.
     *  The object class shall be inherited by all other game entities such as towers, enemies, etc.
     */ 
    class Object
    {
        public:
            Object(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite);
            virtual sf::Vector2<float> getPosition(); 
            virtual sf::CircleShape getHitbox();
            virtual sf::Texture getSprite();
            virtual void setPosition(sf::Vector2<float> position);

        protected:
            sf::Vector2<float> position_;
            sf::CircleShape hitbox_;
            sf::Texture sprite_;
    };
}
