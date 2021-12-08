#include "tower.hpp"

namespace td {
Tower::Tower(types::Position position, float hitbox, sf::Texture* texture,
             float rotation_angle, unsigned int attack_speed, float range)
    : Object(position, hitbox, texture, rotation_angle),
      attack_speed_(attack_speed),
      range_(range) {}

Tower::Tower(types::Position position, float rotation_angle,
             unsigned int attack_speed)
    : Object(position, 1.0f, nullptr, rotation_angle),
      attack_speed_(attack_speed),
      range_(1.0) {}

void Tower::Update(types::Time dt, const td::Game&) {}

unsigned int Tower::getAttackSpeed() const { return attack_speed_; }

float Tower::getRange() const { return range_; }
}  // namespace td
