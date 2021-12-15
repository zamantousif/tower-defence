#include "projectile.hpp"
#include <cmath>

namespace td {
Projectile::Projectile(types::Position position, float hitbox,
                       sf::Texture* texture, float rotation_angle, float damage,
                       bool is_armor_piercing, unsigned int enemy_pierced_count,
                       float speed, float lifetime)
    : Object(position, hitbox, texture, rotation_angle),
      damage_(damage),
      is_armor_piercing_(is_armor_piercing),
      enemy_pierced_count_(enemy_pierced_count),
      speed_(speed),
      lifetime_left_(lifetime) {}

void Projectile::Update(types::Time dt, std::list<Enemy>& enemies,
                        std::list<Projectile>& projectiles) {
  position_.x += dt.asMilliseconds()/100.f*speed_ * cos(rotation_angle_);
  position_.y += dt.asMilliseconds()/100.f*speed_ * sin(rotation_angle_);
  if (speed_ > 0) {
    lifetime_left_ -= dt.asMilliseconds()/100.f*speed_;
  } else {
    lifetime_left_ -= dt.asMilliseconds()/100.f;
  }
  
  if (lifetime_left_ <= 0) {
    this->Delete();
  }
}

void Projectile::Update(types::Time dt) {

}

float Projectile::getDamage() const { return damage_; }

bool Projectile::isArmorPiercing() const { return is_armor_piercing_; }

void Projectile::setEnemyPiercedCount(unsigned int count) {
  enemy_pierced_count_ = count;
}

unsigned int Projectile::getEnemyPiercedCount() const {
  return enemy_pierced_count_;
}

float Projectile::getSpeed() const {
  return speed_;
}

float Projectile::getLifetimeLeft() const {
  return lifetime_left_;
}

}  // namespace td
