#include "tower.hpp"

namespace td {
Tower::Tower(sf::Vector2<float> position, float hitbox, sf::Texture texture,
             float rotation_angle, unsigned int attack_speed, float range)
    : Object(position, hitbox, texture, rotation_angle),
      attack_speed_(attack_speed),
      range_(range) {}

Tower::Tower(sf::Vector2<float> position, float rotation_angle,
             unsigned int attack_speed)
    : Object(position, 1.0f, sf::Texture(), rotation_angle),
      attack_speed_(attack_speed),
      range_(1.0) {}

unsigned int Tower::getAttackSpeed() const { return attack_speed_; }

float Tower::getRange() const { return range_; }
}  // namespace td
