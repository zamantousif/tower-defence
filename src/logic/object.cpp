#include "object.hpp"

namespace td {
Object::Object(types::Position position, float hitboxRadius,
               sf::Texture* texture, float rotation_angle)
    : position_(position),
      hitboxRadius_(hitboxRadius),
      texture_(texture),
      rotation_angle_(rotation_angle) {}

types::Position Object::getPosition() const { return position_; }

float Object::getHitboxRadius() const { return hitboxRadius_; }

const sf::Texture* Object::getTexture() const { return texture_; }

sf::Texture* Object::getTexture() { return texture_; }

void Object::setPosition(types::Position position) { position_ = position; }

void Object::setRotation(float angle) { rotation_angle_ = angle; }

float Object::getRotation() const { return rotation_angle_; }
}  // namespace td
