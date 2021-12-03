#pragma once

#include <SFML/Graphics.hpp>
#include "projectile.hpp"

namespace td::projectiles
{
    class Strong_projectile : public Projectile
    {
        public:
            /// \brief Projectile constructor
            /// \param position             Position of the projectile
            /// \param hitbox               Shape representing the region occupied by the projectile
            /// \param sprite               Texture of the projectile
            /// \param rotation_angle       Orientation, in radians of the projectile
            /// \param damage               Damage % of the projectile
            /// \param is_armor_piercing    Status of projectile armor
            /// \param enemy_pierced_count  Number of enemies pierced by the projectile before disappearing
            Strong_projectile(sf::Vector2<float> position, float rotation_angle);

              void Update(td::types::Time dt) { (void)dt; }
    };
}