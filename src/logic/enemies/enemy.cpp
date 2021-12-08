#include "enemy.hpp"

namespace td {
Enemy::Enemy(types::Position position, float hitbox, sf::Texture* texture,
             float health, int move_speed, float bounty, bool armored,
             float distance_moved, unsigned int slowed_level)
    : Object(position, hitbox, texture),
      health_(health),
      move_speed_(move_speed),
      bounty_(bounty),
      armored_(armored),
      distance_moved_(distance_moved),
      slowed_level_(slowed_level) {}

void Enemy::Update(td::types::Time dt) { (void)dt; }

float Enemy::getHealth() const { return health_; }

int Enemy::getMoveSpeed() const { return move_speed_; }

float Enemy::getBounty() const { return bounty_; }

bool Enemy::isArmored() const { return armored_; }

float Enemy::getDistanceMoved() const { return distance_moved_; }

void Enemy::setDistanceMoved(float distance) { distance_moved_ = distance; }

void Enemy::setSlowedLevel(unsigned int level) { slowed_level_ = level; }

unsigned int Enemy::getSlowedLevel() const { return slowed_level_; }
}  // namespace td
