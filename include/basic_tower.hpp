#pragma once

#include <SFML/Graphics.hpp>
#include "tower.hpp"

namespace td
{
    ///  \brief //Implementation of our first basic starting tower named basic_tower
    class Basic_tower : public Tower
    {
        public:
            /// \brief Tower constructor
            /// \param position     Position of the tower
            Basic_tower(sf::Vector2<float> position, float rotation_angle = 0.0f);

            /// \brief Get the shooting type of the tower
            /// \return Projectiles shoot by the tower
            virtual std::vector<projectiles::Projectile> shoot(std::vector<projectiles::Projectile>);
    };
}
