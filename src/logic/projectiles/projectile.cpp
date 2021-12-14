#include "projectile.hpp"
#include <cmath>

namespace td {
Projectile::Projectile(types::Position position, float hitbox,
                       sf::Texture* texture, float rotation_angle, float damage,
                       bool is_armor_piercing, unsigned int enemy_pierced_count)
    : Object(position, hitbox, texture, rotation_angle),
      damage_(damage),
      is_armor_piercing_(is_armor_piercing),
      enemy_pierced_count_(enemy_pierced_count),
      exhausted_(false) {}

void Projectile::Update(types::Time dt, const td::Game&) {}

void Projectile::Update(types::Time dt) {
  position_.x += dt.asMilliseconds()/10.f * cos(rotation_angle_);
  position_.y += dt.asMilliseconds()/10.f * sin(rotation_angle_);
}

float Projectile::getDamage() const { return damage_; }

bool Projectile::isArmorPiercing() const { return is_armor_piercing_; }

void Projectile::setEnemyPiercedCount(unsigned int count) {
  enemy_pierced_count_ = count;
}

unsigned int Projectile::getEnemyPiercedCount() const {
  return enemy_pierced_count_;
}

bool Projectile::isExhausted() const { return exhausted_; }
}  // namespace td