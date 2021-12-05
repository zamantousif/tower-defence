#include "tower.hpp"

#include <cmath>
#include <cstdlib>

namespace td {
Tower::Tower(types::Position position, float hitbox, sf::Texture* texture,
             float rotation_angle, unsigned int attack_speed, float range,
             unsigned int level, char targetTo)
    : Object(position, hitbox, texture, rotation_angle),
      attack_speed_(attack_speed),
      range_(range),
      level_(level),
      targetTo_(targetTo) {}

Tower::Tower(types::Position position, float rotation_angle,
             unsigned int attack_speed)
    : Object(position, 1.0f, nullptr, rotation_angle),
      attack_speed_(attack_speed),
      range_(1.0) {}

unsigned int Tower::getAttackSpeed() const { return attack_speed_; }

float Tower::getRange() const { return range_; }

sf::Vector2<float> Tower::getPosition() { return position_; }

float Tower::getHitbox() { return hitboxRadius_; }

void Tower::setRotation(float angle) { rotation_angle_ = angle; }

float Tower::getRotation() { return rotation_angle_; }

unsigned int Tower::getLevel() { return level_; }

char Tower::getTargetType() { return targetTo_; }

void Tower::setTargetType(char targetType) { targetTo_ = targetType; }

Enemy* Tower::getTarget(std::vector<Enemy*> enemies) {
  std::vector<Enemy*> enemiesInRange;
  float towerxpos = this->getPosition().x;
  float towerypos = this->getPosition().y;
  for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end();
       it++) {
    float enemyxpos = (*it)->getPosition().x;
    float enemyypos = (*it)->getPosition().y;
    if (sqrt(pow(enemyxpos - towerxpos, 2) + pow(enemyypos - towerypos, 2)) <=
        this->getRange()) {
      enemiesInRange.push_back(*it);
    }
  }
  if (this->getTargetType() == 'c') {
    if (enemiesInRange.size() == 0) return NULL;
    Enemy* closestEnemy;
    float closestPos = this->getRange();
    for (std::vector<Enemy*>::iterator it = enemiesInRange.begin();
         it != enemiesInRange.end(); it++) {
      float enemyxpos = (*it)->getPosition().x;
      float enemyypos = (*it)->getPosition().y;
      float currentPos =
          sqrt(pow(enemyxpos - towerxpos, 2) + pow(enemyypos - towerypos, 2));
      if (currentPos <= closestPos) {
        closestPos = currentPos;
        closestEnemy = *it;
      }
    }
    return closestEnemy;
  } else if (this->getTargetType() == 's') {
    if (enemiesInRange.size() == 0) return NULL;
    Enemy* strongestEnemy;
    float strongestHP = 0;
    for (std::vector<Enemy*>::iterator it = enemiesInRange.begin();
         it != enemiesInRange.end(); it++) {
      float currentHealth = (*it)->getHealth();
      if (currentHealth >= strongestHP) {
        strongestHP = currentHealth;
        strongestEnemy = *it;
      }
    }
    return strongestEnemy;
  } else if (this->getTargetType() == 'f') {
    if (enemiesInRange.size() == 0) return NULL;
    Enemy* furthestEnemy;
    float furthestDistance = 0;
    for (std::vector<Enemy*>::iterator it = enemiesInRange.begin();
         it != enemiesInRange.end(); it++) {
      float currentDistance = (*it)->getDistanceMoved();
      if (currentDistance >= furthestDistance) {
        furthestDistance = currentDistance;
        furthestEnemy = *it;
      }
    }
    return furthestEnemy;
  }
  throw "Target type not recognized";
}

types::Position Tower::GetProjectStartPos(types::Position centre, float radius,
                                   float angle) {
  types::Position result;
  result.x = centre.x + radius + cos(angle);  // angle should be in radians
  result.y = centre.y + radius + sin(angle);
  return result;
}
}  // namespace td
