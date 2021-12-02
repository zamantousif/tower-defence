#include "object.hpp"

namespace td {
Object::Object(sf::Vector2<float> position, float hitbox,
               sf::Texture texture, float rotation_angle)
    : position_(position),
      hitbox_(hitbox),
      texture_(texture),
      rotation_angle_(rotation_angle) {}

void Update(sf::Time dt) { (void)dt; }

sf::Vector2<float> Object::getPosition() const { return position_; }

float Object::getHitbox() const { return hitbox_; }

sf::Texture Object::getTexture() const { return texture_; }

void Object::setPosition(sf::Vector2<float> position) { position_ = position; }

void Object::setRotation(float angle) { rotation_angle_ = angle; }

float Object::getRotation() const { return rotation_angle_; }
}  // namespace td
