#pragma once

#include <SFML/Graphics.hpp>
#include <Object.hpp>

namespace td
{
    ///  \brief Enemy class represents the blueprint of a basic enemy in the game.
    ///  The base enemy class can be derived further to create towers with special powers. 
    class Enemy : public Object
    {
        public:
            /// \brief Enemy constructor
            /// \param position         Position of the enemy
            /// \param hitbox           Shape around the enemy where damage is effective
            /// \param sprite           Texture of the enemy
            /// \param health           Health of the enemy
            /// \param moveSpeed        Movement speed of the enemy
            /// \param bounty           Bounty of the enemy
            /// \param armored          Status of enemy armor
            /// \param movedDistance    Total distance moved on the path by the enemy
            Enemy(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float health = 100.0f, int moveSpeed = 1, 
            float bounty = 0.0f, bool armored = false, float movedDistance = 0.0f);

            /// \brief Get the position of the enemy
            /// \return Position of the enemy
            virtual sf::Vector2<float> getPosition();

            /// \brief Get the remaining health of the enemy
            /// \return Remaining health of the enemy
            virtual float getHealth();

            /// \brief Get the movement speed of the enemy
            /// \return Movement speed of the enemy
            virtual int getMoveSpeed();

            /// \brief Do some action when the enemy dies
            virtual void doUponDeath();

            /// \brief Get the bounty of the enemy
            /// \return Bounty of the enemy
            virtual float getBounty();

            /// \brief Status of enemy armor
            /// \return True if the enemy is armored otherwise false
            virtual bool isArmored();

            /// \brief Set the total distance moved on the path by the enemy
            virtual void setDistanceMoved(float distance);

        protected:
            float health_;          ///< Remaining health of the enemy
            int moveSpeed_;         ///< Movement speed of the enemy
            int bounty_;            ///< Bounty of the enemy
            bool armored_;          ///< Status of enemy armor
            float movedDistance_;   ///< Total distance moved on the path by the enemy
    };
}
