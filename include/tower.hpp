#pragma once

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "projectile.hpp"

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
            /// \param level        Level of the tower
            Tower(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float rotation_angle = 0.0f, unsigned int attack_speed = 1U, float range = 1.0f, unsigned int level = 1);
            
            /// \brief Tower constructor
            /// \param position     Position of the tower
            /// \param attack_speed  Attack speed of the tower
            explicit Tower(sf::Vector2<float> position, float rotation_angle, unsigned int attack_speed);

            /// \brief Get the position of the tower
            /// \return Position of the tower
            virtual sf::Vector2<float> getPosition();

            /// \brief Get the shape representing region of the tower
            /// \return Shape representing the region occupied by the tower
            virtual sf::CircleShape getHitbox();

            /// \brief Set the rotation of the tower
            /// \param angle    Orientation, in radians of the tower
            virtual void setRotation(float angle);

            /// \brief Get the orientation of the tower
            /// \return Orientation, in radians of the tower
            virtual float getRotation();

            /// \brief Get the attack speed of the tower
            /// \return Attack speed of the tower
            virtual unsigned int getAttackSpeed();

            /// \brief Get the attack range of the tower
            /// \return Attack range of the tower
            virtual float getRange();

             /// \brief Get the level of the tower
            /// \return Level of the tower
            virtual unsigned int getLevel();

            /// \brief Get the shooting type of the tower
            /// \return Projectiles shoot by the tower
            virtual Projectile shoot() = 0;

        protected:
            unsigned int attack_speed_;  ///< Attack speed of the tower
            float range_;               ///< Attack range of the tower
            unsigned int level_;        ///< Level of the tower
    };
}
