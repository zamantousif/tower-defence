#ifndef TOWER_DEFENCE_OBJECT_CLASS
#define TOWER_DEFENCE_OBJECT_CLASS

#include <SFML/Graphics.hpp>

namespace towerdefence
{
    class Object
    {
        public:
            Object(sf::Vector2<unsigned int> position, sf::CircleShape hitbox, sf::Texture sprite);
            sf::Vector2<unsigned int> getPosition(); 
            sf::CircleShape getHitbox();
            sf::Texture getSprite();

        protected:
            sf::Vector2<unsigned int> position_;
            sf::CircleShape hitbox_;
            sf::Texture sprite_;
    };
}

#endif
