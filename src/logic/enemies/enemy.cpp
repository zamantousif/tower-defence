#include "enemy.hpp"

#include <list>

namespace td {
Enemy::Enemy(types::Position position, float hitbox, sf::Texture* texture,
             float health, int move_speed, float bounty, bool armored,
             float distance_moved)
    : Object(position, hitbox, texture),
      health_(health),
      move_speed_(move_speed),
      bounty_(bounty),
      armored_(armored),
      distance_moved_(distance_moved) {}

void Enemy::Update(td::types::Time dt) { (void)dt; }

Enemy Enemy::createBasicCockroach(types::Position startOfTheMap,
                                  sf::Texture* texture) {
  Enemy basicCockroach =
      Enemy(startOfTheMap, 1.0f, texture, 200, 10, 10, false, 0);
  return basicCockroach;
}

Enemy Enemy::createFly(types::Position startOfTheMap, sf::Texture* texture) {
  Enemy fly = Enemy(startOfTheMap, 1.0f, texture, 150, 20, 14, false, 0);
  return fly;
}

Enemy Enemy::createBeetle(types::Position startOfTheMap, sf::Texture* texture) {
  Enemy beetle = Enemy(startOfTheMap, 1.5f, texture, 300, 10, 20, true, 0);
  return beetle;
}

Enemy Enemy::createDragonfly(types::Position startOfTheMap,
                             sf::Texture* texture) {
  Enemy dragonfly = Enemy(startOfTheMap, 2.0f, texture, 4000, 10, 400, true, 0);
  return dragonfly;
}

float Enemy::getHealth() const { return health_; }

int Enemy::getMoveSpeed() const { return move_speed_; }

float Enemy::getBounty() const { return bounty_; }

bool Enemy::isArmored() const { return armored_; }

float Enemy::getDistanceMoved() const { return distance_moved_; }

void Enemy::setDistanceMoved(float distance) { distance_moved_ = distance; }
}  // namespace td
