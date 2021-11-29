#pragma once

#include <SFML/Graphics.hpp>
#include "object.hpp"

namespace td
{
    ///  \brief Enemy class represents the blueprint of a basic enemy in the game.
    ///  The base enemy class can be derived further to create towers with special powers. 
    class Enemy : public Object
    {
        public:
            /// \brief Enemy constructor
            /// \param position         Position of the enemy
            /// \param hitbox           Shape representing the region occupied by the enemy
            /// \param sprite           Texture of the enemy
            /// \param health           Health of the enemy
            /// \param move_speed       Movement speed of the enemy
            /// \param bounty           Bounty of the enemy
            /// \param armored          Status of enemy armor
            /// \param moved_distance   Total distance moved on the path by the enemy
            Enemy(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float health = 100.0f, int move_speed = 1, 
            float bounty = 0.0f, bool armored = false, float distance_moved = 0.0f);

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
            virtual void DoUponDeath();

            /// \brief Get the bounty of the enemy
            /// \return Bounty of the enemy
            virtual float getBounty();

            /// \brief Status of enemy armor
            /// \return True if the enemy is armored otherwise false
            virtual bool isArmored();

            virtual float getDistanceMoved();

            /// \brief Set the total distance moved on the path by the enemy
            virtual void setDistanceMoved(float distance);

        protected:
            float health_;              ///< Remaining health of the enemy
            int move_speed_;            ///< Movement speed of the enemy
            int bounty_;                ///< Bounty of the enemy
            bool armored_;              ///< Status of enemy armor
            float distance_moved_;      ///< Total distance moved on the path by the enemy
    };
}
