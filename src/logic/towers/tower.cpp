#include "tower.hpp"

namespace td {
  Tower::Tower(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite,
               float rotation_angle, unsigned int attack_speed, float range)
      : Object(position, hitbox, sprite, rotation_angle), attack_speed_(attack_speed), range_(range) {}

  Tower::Tower(sf::Vector2<float> position, float rotation_angle, unsigned int attack_speed)
      : Object(position, sf::CircleShape(1.0f, 30UL), sf::Texture(), rotation_angle),
               attack_speed_(attack_speed), range_(1.0) {}

  unsigned int Tower::getAttackSpeed() const {
    return attack_speed_;
  }

  float Tower::getRange() const {
    return range_;
  }
}
