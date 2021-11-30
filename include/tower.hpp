#pragma once

#include <SFML/Graphics.hpp>
#include "object.hpp"

namespace td
{
    ///  \brief Tower class represents the blueprint of a basic tower in the game.
    ///  The base tower class can be derived further to create towers with special powers. 
    class Tower : public Object
    {
        public:
            /// \brief Tower constructor
            /// \param position     Position of the tower
            /// \param hitbox       Shape representing the region occupied by the tower
            /// \param sprite       Texture of the tower
            /// \param attack_speed  Attack speed of the tower
            /// \param range        Attack range of the tower 
            Tower(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float rotation_angle = 0.0f, unsigned int attack_speed = 1U, float range = 1.0f);
            
            /// \brief Tower constructor
            /// \param position     Position of the tower
            /// \param attack_speed  Attack speed of the tower
            explicit Tower(sf::Vector2<float> position, float rotation_angle, unsigned int attack_speed);

            /// \brief Get the attack speed of the tower
            /// \return Attack speed of the tower
            virtual unsigned int getAttackSpeed() const;

            /// \brief Get the attack range of the tower
            /// \return Attack range of the tower
            virtual float getRange() const;

        protected:
            unsigned int attack_speed_;  ///< Attack speed of the tower
            float range_;               ///< Attack range of the tower
    };
}
