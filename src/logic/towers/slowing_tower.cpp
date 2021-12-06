#include "slowing_tower.hpp"

#include <SFML/Graphics.hpp>

namespace td {
float hitbox_slowing = 1.0f;  // parameters radius and pointCount

unsigned int attack_speed_slowing = 10;  // can adjust these later

float range_slowing = 7.0f;

Slowing_tower::Slowing_tower(sf::Vector2<float> position, float rotation_angle, sf::Texture* texture)
    : Tower(position, hitbox_slowing, texture, nullptr, rotation_angle,
            attack_speed_slowing, range_slowing) {}

std::list<projectiles::Projectile> Slowing_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
  // add implementation here
}

}  // namespace td