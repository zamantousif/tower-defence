#include <SFML/Graphics.hpp>
#include "tower.hpp"

namespace td
{
    ///  \brief //Implementation of the slowing tower that slows down enemies in its range
    class Slowing_tower : public Tower
    {
        public:
            /// \brief Tower constructor
            /// \param position     Position of the tower
            Slowing_tower(sf::Vector2<float> position, float rotation_angle = 0.0f);

            /// \brief Get the shooting type of the tower
            /// \return Projectiles shoot by the tower
            virtual projectiles::Projectile shoot();
    };
}