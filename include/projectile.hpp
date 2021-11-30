#pragma once

#include <SFML/Graphics.hpp>
#include "object.hpp"

namespace td
{
    class Projectile : public Object
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
            Projectile(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float rotation_angle, unsigned int damage, 
            bool is_armor_piercing, unsigned int enemy_pierced_count);

            /// \brief Get the damage % of the projectile
            /// \return Damage % of the projectile
            unsigned int getDamage() const;

            /// \brief Get the armor piercing status of the projectile
            /// \return True if projectile has armor piercing active, false otherwise
            bool isArmorPiercing() const;

            /// \brief Get the number of enemies pierced by the projectile
            /// \return Number of enemies pierced by the projectile
            unsigned int getEnemyPiercedCount() const;

        protected:
            unsigned int damage_;                   ///< Damage % of the projectile
            bool is_armor_piercing_;                ///< Armor piercing status of the projectile
            unsigned int enemy_pierced_count_;      ///< Number of enemies pierced by the projectile before disappearing
    };
}
