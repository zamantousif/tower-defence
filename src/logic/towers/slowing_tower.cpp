#include "slowing_tower.hpp"

#include <SFML/Graphics.hpp>

namespace td {
float hitbox_slowing = 1.0f;  // parameters radius and pointCount

sf::Texture* sprite_slowing = nullptr;  // picture of the tower to here

unsigned int attack_speed_slowing = 10;  // can adjust these later

float range_slowing = 7.0f;

Slowing_tower::Slowing_tower(sf::Vector2<float> position, float rotation_angle)
    : Tower(position, hitbox_slowing, sprite_slowing, rotation_angle,
            attack_speed_slowing, range_slowing) {}

std::list<projectiles::Projectile> Slowing_tower::shoot(
    std::list<projectiles::Projectile> vector) {
  // add implementation here
}

}  // namespace td