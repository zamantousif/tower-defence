#include "projectile.hpp"

namespace td {
Projectile::Projectile(types::Position position, float hitbox,
                       types::Texture texture, float rotation_angle,
                       float damage, bool is_armor_piercing,
                       unsigned int enemy_pierced_count)
    : Object(position, hitbox, texture, rotation_angle),
      damage_(damage),
      is_armor_piercing_(is_armor_piercing),
      enemy_pierced_count_(enemy_pierced_count),
      exhausted_(false) {}

void Projectile::Update(types::Time dt, const td::Game&) {}

float Projectile::getDamage() const { return damage_; }

bool Projectile::isArmorPiercing() const { return is_armor_piercing_; }

unsigned int Projectile::getEnemyPiercedCount() const {
  return enemy_pierced_count_;
}

bool Projectile::isExhausted() const { return exhausted_; }
}  // namespace td
