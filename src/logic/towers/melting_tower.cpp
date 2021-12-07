#include "melting_tower.hpp"

#include <SFML/Graphics.hpp>

namespace td {
float hitbox_melting = 1.0f;  // parameters radius and pointCount

unsigned int attack_speed_melting = 10;  // can adjust these later

float range_melting = 10.0f;

std::vector<unsigned int> upgrade_costs_melting = { 100, 100, 150 };

unsigned int Melting_tower::getUpgradeCost()
{
  return upgrade_costs_melting.at(level_-1);
}

Melting_tower::Melting_tower(sf::Vector2<float> position, float rotation_angle, sf::Texture* texture)
    : Tower(position, hitbox_melting, texture, nullptr, rotation_angle,
            attack_speed_melting, range_melting) {}

std::list<projectiles::Projectile> Melting_tower::shoot(
    std::list<projectiles::Projectile> projectiles) {
  // add implementation here
}

}  // namespace td