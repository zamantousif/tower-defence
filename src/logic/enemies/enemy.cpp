#include "enemy.hpp"

namespace td {
Enemy::Enemy(types::Position position, float hitbox, types::Texture texture,
             float health, int move_speed, float bounty, bool armored,
             float distance_moved)
    : Object(position, hitbox, texture),
      health_(health),
      move_speed_(move_speed),
      bounty_(bounty),
      armored_(armored),
      distance_moved_(distance_moved) {}

float Enemy::getHealth() const { return health_; }

int Enemy::getMoveSpeed() const { return move_speed_; }

float Enemy::getBounty() const { return bounty_; }

bool Enemy::isArmored() const { return armored_; }

float Enemy::getDistanceMoved() const { return distance_moved_; }


  void Enemy::setDistanceMoved(float distance) { distance_moved_ = distance; }

}
