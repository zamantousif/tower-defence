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
            Object(sf::Vector2<unsigned int> position, sf::CircleShape hitbox, sf::Texture sprite);
            virtual sf::Vector2<unsigned int> getPosition(); 
            virtual sf::CircleShape getHitbox();
            virtual sf::Texture getSprite();

        protected:
            sf::Vector2<unsigned int> position_;
            sf::CircleShape hitbox_;
            sf::Texture sprite_;
    };
}
