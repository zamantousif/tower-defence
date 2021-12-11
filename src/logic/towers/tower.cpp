#include "tower.hpp"

#include <cmath>
#include <cstdlib>

namespace td {
Tower::Tower(types::Position position, float hitbox, sf::Texture* texture,
             sf::Texture* texture_projectile, float rotation_angle,
             unsigned int attack_speed, float range, unsigned int level,
             types::Targeting targeting)
    : Object(position, hitbox, texture, rotation_angle),
      attack_speed_(attack_speed),
      range_(range),
      level_(level),
      targeting_(targeting),
      texture_projectile_(texture_projectile) {}

Tower::Tower(types::Position position, float rotation_angle,
             unsigned int attack_speed)
    : Object(position, 1.0f, nullptr, rotation_angle),
      attack_speed_(attack_speed),
      range_(1.0) {}

void Tower::Update(types::Time dt, const td::Game&) {}

unsigned int Tower::getAttackSpeed() const { return attack_speed_; }

float Tower::getRange() const { return range_; }

unsigned int Tower::getLevel() const { return level_; }

const unsigned int Tower::getMoneySpent() const {
  return money_spent_on_tower_;
}

void Tower::setMoneySpent(unsigned int value) { money_spent_on_tower_ = value; }

types::Targeting Tower::getTargeting() const { return targeting_; }

void Tower::setTargeting(types::Targeting targeting) { targeting_ = targeting; }

std::optional<const Enemy*> Tower::getTarget(
    const std::vector<Enemy>& enemies) {
  std::vector<Enemy> enemiesInRange;
  float towerxpos = position_.x;
  float towerypos = position_.y;
  for (auto it = enemies.cbegin(); it != enemies.cend(); it++) {
    float enemyxpos = (*it).getPosition().x;
    float enemyypos = (*it).getPosition().y;
    if (sqrt(pow(enemyxpos - towerxpos, 2) + pow(enemyypos - towerypos, 2)) <=
        range_ + (*it).getHitboxRadius()) {
      enemiesInRange.push_back(*it);
    }
  }
  types::Position zeroPosition;
  zeroPosition.x = 0;
  zeroPosition.y = 0;
  sf::Texture* texture;
  Enemy noEnemiesFound =
      Enemy(zeroPosition, 0.0f, texture, 0, 0, 0, false, 0, 0);
  // return this noEnemiesFound enemy if no enemies in tower range
  switch (targeting_) {
    case types::kClose: {
      if (enemiesInRange.size() == 0) return std::nullopt;
      Enemy closestEnemy = enemiesInRange.at(0);
      float closestPos = range_;
      for (std::vector<Enemy>::iterator it = enemiesInRange.begin();
           it != enemiesInRange.end(); it++) {
        float enemyxpos = (*it).getPosition().x;
        float enemyypos = (*it).getPosition().y;
        float currentPos = static_cast<float>(sqrt(
            pow(enemyxpos - towerxpos, 2) + pow(enemyypos - towerypos, 2)));
        if (currentPos <= closestPos) {
          closestPos = currentPos;
          closestEnemy = (*it);
        }
      }
      return &closestEnemy;
    }
    case types::kStrong: {
      if (enemiesInRange.size() == 0) return std::nullopt;
      Enemy strongestEnemy = enemiesInRange.at(0);
      float strongestHP = 0;
      for (std::vector<Enemy>::iterator it = enemiesInRange.begin();
           it != enemiesInRange.end(); it++) {
        float currentHealth = (*it).getHealth();
        if (currentHealth >= strongestHP) {
          strongestHP = currentHealth;
          strongestEnemy = *it;
        }
      }
      return &strongestEnemy;
    }
    case types::kFirst: {
      if (enemiesInRange.size() == 0) return std::nullopt;
      Enemy furthestEnemy = enemiesInRange.at(0);
      float furthestDistance = 0;
      for (std::vector<Enemy>::iterator it = enemiesInRange.begin();
           it != enemiesInRange.end(); it++) {
        float currentDistance = (*it).getDistanceMoved();
        if (currentDistance >= furthestDistance) {
          furthestDistance = currentDistance;
          furthestEnemy = *it;
        }
      }
      return &furthestEnemy;
    }
    case types::kLast: {
      if (enemiesInRange.size() == 0) return std::nullopt;
      Enemy lastEnemy = enemiesInRange.at(0);
      float lastDistance = -1;
      for (std::vector<Enemy>::iterator it = enemiesInRange.begin();
           it != enemiesInRange.end(); it++) {
        float currentDistance = (*it).getDistanceMoved();
        if (currentDistance <= lastDistance || lastDistance == -1) {
          lastDistance = currentDistance;
          lastEnemy = *it;
        }
      }
      return &lastEnemy;
    }
  }
  throw "Target type not recognized";
}

types::Position Tower::GetProjectStartPos() {
  types::Position result;
  result.x =
      position_.x + hitboxRadius_ * cos(rotation_angle_);  // angle in radians
  result.y = position_.y + hitboxRadius_ * sin(rotation_angle_);
  return result;
}
}  // namespace td
