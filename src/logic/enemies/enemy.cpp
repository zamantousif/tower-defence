#include "enemy.hpp"

#include <iostream>
#include <list>
#include "collision.hpp"
//#include "game.hpp"

#include "collision.hpp"

namespace td {
class Game;
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
      slowed_level_(slowed_level),
      at_end_of_path_(false) {}

Enemy::Enemy(const Enemy& enemy) : Object(enemy) {
  health_ = enemy.max_health_;
  max_health_ = enemy.max_health_;
  move_speed_ = enemy.move_speed_;
  bounty_ = enemy.bounty_;
  armored_ = enemy.armored_;
  distance_moved_ = enemy.distance_moved_;
  slowed_level_ = enemy.slowed_level_;
  at_end_of_path_ = enemy.at_end_of_path_;
}

void Enemy::Update(types::Time dt, const std::vector<types::Position>& path) {
  float slowing_ratio = 1.0f;
  if (slowed_level_ > 0) {
    slowing_ratio = 1.0f - (slowed_level_+2)*0.1f;
  }
  float move_by = move_speed_ * slowing_ratio * dt.asMilliseconds() / 1000.f;
  slowed_level_ = 0;
  size_t i = 0;  // iterating index
  float distance_counter = 0;

  while (i < path.size() - 1) {
    distance_counter += EuclideanDistance(path[i], path[i + 1]);
    if (distance_counter > distance_moved_) {
      float leftover_distance = distance_moved_ - (distance_counter - EuclideanDistance(path[i], path[i + 1]));
      sf::Vector2f direction = (path[i + 1] - path[i]);
      double direction_magnitude = EuclideanDistance(path[i], path[i + 1]);
      direction.x /= direction_magnitude;
      direction.y /= direction_magnitude;

      position_ = path[i] + (direction * leftover_distance);
      sf::Vector2f rotation_direction = (path[i + 1] - path[i]);
 
      if (direction.x > 0) {
        rotation_angle_ = atan(direction.y/direction.x);
      } else if (direction.x < 0) {
        rotation_angle_ = PI+atan(-direction.y/direction.x);
      } else if (direction.y > 0) {
        rotation_angle_ = PI/2;
      } else {
        rotation_angle_ = 3*PI/2;
      }

      distance_moved_ += move_by;
      return;
    }
    i++;
  }
  at_end_of_path_ = true;
  this->Delete();
}

bool Enemy::TakeDamage(float damage, bool is_armor_piercing) {
  if (health_ <= 0) {
    return false;
  }
  health_ -= damage;
  if (armored_ && is_armor_piercing) {  //armored enemies take double damage from armor_piercing damage sources
    health_ -= damage;
  }
  if (health_ <= 0) {
    health_ = 0;
    this->Delete();
  }
  return true;
}

Enemy Enemy::createBasicCockroach(types::Position startOfTheMap,
                                  sf::Texture* texture) {
  Enemy basic_cockroach =
      Enemy(startOfTheMap, 1.0f, texture, 200, 10, 10, false, 0);
  return basic_cockroach;
}

Enemy Enemy::createFly(types::Position startOfTheMap, sf::Texture* texture) {
  Enemy fly = Enemy(startOfTheMap, 1.0f, texture, 150, 20, 14, false, 0);
  return fly;
}

Enemy Enemy::createBeetle(types::Position startOfTheMap, sf::Texture* texture) {
  Enemy beetle = Enemy(startOfTheMap, 1.5f, texture, 500, 10, 20, true, 0);
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

bool Enemy::isAtEndOfPath() const { return at_end_of_path_; }

float Enemy::getDistanceMoved() const { return distance_moved_; }

void Enemy::setDistanceMoved(float distance) { distance_moved_ = distance; }

void Enemy::setSlowedLevel(unsigned int level) { slowed_level_ = level; }

unsigned int Enemy::getSlowedLevel() const { return slowed_level_; }

}  // namespace td
