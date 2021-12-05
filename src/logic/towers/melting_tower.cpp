#include "melting_tower.hpp"

#include <SFML/Graphics.hpp>

namespace td {
float hitbox_melting = 1.0f;  // parameters radius and pointCount

sf::Texture* sprite_melting = nullptr;  // picture of the tower to here

unsigned int attack_speed_melting = 10;  // can adjust these later

float range_melting = 10.0f;

Melting_tower::Melting_tower(sf::Vector2<float> position, float rotation_angle)
    : Tower(position, hitbox_melting, sprite_melting, rotation_angle,
            attack_speed_melting, range_melting) {}

std::list<projectiles::Projectile> Melting_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
  // add implementation here
}

}  // namespace td