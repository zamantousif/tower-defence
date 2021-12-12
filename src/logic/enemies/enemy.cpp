#include "enemy.hpp"

#include <list>

namespace td {
Enemy::Enemy(types::Position position, float hitbox, sf::Texture* texture,
             float health, int move_speed, int bounty, bool armored,
             float distance_moved, unsigned int slowed_level)
    : Object(position, hitbox, texture),
      health_(health),
      max_health_(health),
      move_speed_(move_speed),
      bounty_(bounty),
      armored_(armored),
      distance_moved_(distance_moved),
      slowed_level_(slowed_level) {}

void Enemy::Update(types::Time dt, const td::Game& game) {
  //Move position of enemy
}
Enemy::Enemy(const Enemy& enemy) : Object(enemy) {
  health_ = enemy.max_health_;
  max_health_ = enemy.max_health_;
  move_speed_ = enemy.move_speed_;
  bounty_ = enemy.bounty_;
  armored_ = enemy.armored_;
  distance_moved_ = enemy.distance_moved_;
  slowed_level_ = enemy.slowed_level_;
}

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

void Enemy::setHealth(float health_decrease) {
  health_ = health_ - health_decrease;
}

float Enemy::getMaxHealth() const { return max_health_; }

int Enemy::getMoveSpeed() const { return move_speed_; }

int Enemy::getBounty() const { return bounty_; }

bool Enemy::isArmored() const { return armored_; }

float Enemy::getDistanceMoved() const { return distance_moved_; }

void Enemy::setDistanceMoved(float distance) { distance_moved_ = distance; }

void Enemy::setSlowedLevel(unsigned int level) { slowed_level_ = level; }

unsigned int Enemy::getSlowedLevel() const { return slowed_level_; }

}  // namespace td
