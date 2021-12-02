#include "object.hpp"

namespace td {
Object::Object(sf::Vector2<float> position, sf::CircleShape hitbox,
               sf::Texture sprite, float rotation_angle)
    : position_(position),
      hitbox_(hitbox),
      sprite_(sprite),
      rotation_angle_(rotation_angle) {}

void Update(sf::Time dt) { (void)dt; }

sf::Vector2<float> Object::getPosition() const { return position_; }

sf::CircleShape Object::getHitbox() const { return hitbox_; }

sf::Texture Object::getSprite() const { return sprite_; }

void Object::setPosition(sf::Vector2<float> position) { position_ = position; }

void Object::setRotation(float angle) { rotation_angle_ = angle; }

float Object::getRotation() const { return rotation_angle_; }
}  // namespace td
