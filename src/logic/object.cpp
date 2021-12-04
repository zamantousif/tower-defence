#include "object.hpp"

namespace td {
Object::Object(types::Position position, float hitboxRadius, types::Texture texture,
               float rotation_angle)
    : position_(position),
      hitboxRadius_(hitboxRadius),
      texture_(texture),
      rotation_angle_(rotation_angle) {}

void Update(types::Time dt, const td::Game& game) {}

types::Position Object::getPosition() const { return position_; }

float Object::getHitbox() const { return hitboxRadius_; }

types::Texture Object::getTexture() const { return texture_; }

void Object::setPosition(types::Position position) { position_ = position; }

void Object::setRotation(float angle) { rotation_angle_ = angle; }

float Object::getRotation() const { return rotation_angle_; }
}  // namespace td
