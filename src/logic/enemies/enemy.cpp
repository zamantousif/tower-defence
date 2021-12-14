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
      slowed_level_(slowed_level) {}

Enemy::Enemy(const Enemy& enemy) : Object(enemy) {
  health_ = enemy.max_health_;
  max_health_ = enemy.max_health_;
  move_speed_ = enemy.move_speed_;
  bounty_ = enemy.bounty_;
  armored_ = enemy.armored_;
  distance_moved_ = enemy.distance_moved_;
  slowed_level_ = enemy.slowed_level_;
}

void Enemy::Update(types::Time dt, const std::vector<types::Position>& path) {
  // std::cout << position_.x << std::endl;
  distance_moved_ += move_speed_ * dt.asMilliseconds() / 1000.f;
  size_t i = 0;  // iterating index
  float distance_counter = 0;
  // position_.x += 1;
  while (i < path.size() - 2) {
    distance_counter += EuclideanDistance(path[i], path[i + 1]);
    if (distance_counter > distance_moved_) {
      float displacement_x = (path[i + 1].x - path[i].x) /
                             EuclideanDistance(path[i], path[i + 1]) *
                             (distance_moved_ - distance_counter);
      float displacement_y = (path[i + 1].y - path[i].y) /
                             EuclideanDistance(path[i], path[i + 1]) *
                             (distance_moved_ - distance_counter);
      position_.x = path[i].x + displacement_x;
      position_.y = path[i].y + displacement_y;
      rotation_angle_ = Angle2D(0, 1, displacement_x, displacement_y);
      std::cout << displacement_x << std::endl;
      break;
    }
    i++;
  }

  /* while (i < path.size() - 2) {
    distance_counter += EuclideanDistance(path[i], path[i + 1]);
    if (distance_counter > distance_moved_) {
      sf::Vector2f direction = (path[i + 1] - path[i]);
      double direction_magnitude = EuclideanDistance(path[i], path[i + 1]);
      direction.x /= direction_magnitude;
      direction.y /= direction_magnitude;

      position_ = path[i] + direction * distance_moved_;
      
      break;
    }
  }*/

  //position_.x += 0.2;
  //position_.y = 780;
  
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

float Enemy::getDistanceMoved() const { return distance_moved_; }

void Enemy::setDistanceMoved(float distance) { distance_moved_ = distance; }

void Enemy::setSlowedLevel(unsigned int level) { slowed_level_ = level; }

unsigned int Enemy::getSlowedLevel() const { return slowed_level_; }

}  // namespace td
