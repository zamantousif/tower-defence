#pragma once

#include <SFML/Graphics.hpp>
#include <Object.hpp>

namespace td
{
    ///  \brief Tower class represents the blueprint of a basic tower in the game.
    ///  The base tower class can be derived further to create towers with special powers. 
    class Tower : public Object
    {
        public:
            /// \brief Tower constructor
            /// \param position     Position of the tower
            /// \param hitbox       Shape around the tower where damage is effective
            /// \param sprite       Texture of the tower
            /// \param attackSpeed  Attack speed of the tower
            /// \param range        Radius of the shape representing damage area of the tower 
            Tower(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, unsigned int attackSpeed, float range);
            
            /// \brief Tower constructor
            /// \param position     Position of the tower
            /// \param attackSpeed  Attack speed of the tower
            Tower(sf::Vector2<float> position, unsigned int attackSpeed);

            /// \brief Get the position of the tower
            /// \return Position of the tower
            virtual sf::Vector2<float> getPosition();

            /// \brief Get the shape around the tower where damage is effective
            /// \return Shape around the tower where damage is effective
            virtual sf::CircleShape getHitbox();

            /// \brief Get the attack speed of the tower
            /// \return Attack speed of the tower
            unsigned int getAttackSpeed();

            /// \brief Get the radius of the shape representing damage area of the tower
            /// \return Radius of the shape representing damage area of the tower
            float getRange();

        protected:
            unsigned int attackSpeed_;  ///< Attack speed of the tower
            float range_;               ///< Radius of the shape representing damage area of the tower
    };
}
