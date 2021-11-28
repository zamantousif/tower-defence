#pragma once

#include <SFML/Graphics.hpp>
#include "tower.hpp"

namespace td
{
    ///  \brief //Implementation of high damage tower that has sparse shooting speed,
    /// but does massive damage on one hit.
    class High_damage_tower : public Tower
    {
        public:
            /// \brief Tower constructor
            /// \param position     Position of the tower
            High_damage_tower(sf::Vector2<float> position, float rotation_angle = 0.0f);

            /// \brief Get the shooting type of the tower
            /// \return Projectiles shoot by the tower
            virtual std::vector<Projectile> shoot(std::vector<Projectile>);
    };
}
