#pragma once

#include <SFML/Graphics.hpp>

namespace td
{
    ///  \brief Object class is an abstract class representing the basic entity of the game.
    ///  The object class shall be inherited by all other game entities such as towers, enemies, etc.     
    class Object
    {
        public:
            /// \brief Object constructor
            /// \param position         Position of the object
            /// \param hitbox           Shape representing the region occupied by the object
            /// \param sprite           Texture of the object
            /// \param rotation_angle   Orientation, in radians of the object
            Object(sf::Vector2<float> position = sf::Vector2f(0.0f, 0.0f), sf::CircleShape hitbox = sf::CircleShape(), sf::Texture sprite = sf::Texture(), float rotation_angle = 0.0f);
            
            /// \brief Get the position of the object
            /// \return Position of the object
            virtual sf::Vector2<float> getPosition();

            /// \brief Get the shape representing region of the object
            /// \return Shape representing the region occupied by the object
            virtual sf::CircleShape getHitbox();
            
            /// \brief Get the texture of the object
            /// \return Texture of the object
            virtual sf::Texture getSprite();
            
            /// \brief Set the position of the object
            /// \param position Position of the object
            virtual void setPosition(sf::Vector2<float> position);
            
            /// \brief Set the rotation of the object
            /// \param angle    Orientation of the object
            virtual void setRotation(float angle);

            /// \brief Get the orientation of the object
            /// \return Orientation, in radians of the object
            virtual float getRotation();

        protected:
            sf::Vector2<float> position_;   ///< Position of the object
            sf::CircleShape hitbox_;        ///< Shape representing the region occupied by the object
            sf::Texture sprite_;            ///< Texture of the object
            float rotation_angle_;          ///< Orientation, in radians of the object
    };
}
