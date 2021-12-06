#include "melting_tower.hpp"

#include <SFML/Graphics.hpp>

namespace td {
float hitbox_melting = 1.0f;  // parameters radius and pointCount

unsigned int attack_speed_melting = 10;  // can adjust these later

float range_melting = 10.0f;

Melting_tower::Melting_tower(sf::Vector2<float> position, float rotation_angle, sf::Texture* texture)
    : Tower(position, hitbox_melting, texture, nullptr, rotation_angle,
            attack_speed_melting, range_melting) {}

std::list<projectiles::Projectile> Melting_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
  // add implementation here
}

}  // namespace td