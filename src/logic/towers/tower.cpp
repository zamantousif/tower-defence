#include "tower.hpp"

#include <cmath>
#include <cstdlib>
#include <limits>

namespace td {
Tower::Tower(types::Position position, float hitbox, sf::Texture* texture,
             sf::Texture* texture_projectile, float rotation_angle,
             unsigned int attack_speed, float range, unsigned int cost, unsigned int upgrade_cost, unsigned int level,
             types::Targeting targeting)
    : Object(position, hitbox, texture, rotation_angle),
      attack_speed_(attack_speed),
      range_(range),
      cost_(cost),
      upgrade_cost_(upgrade_cost),
      level_(level),
      targeting_(targeting),
      texture_projectile_(texture_projectile) {}

Tower::Tower(types::Position position, float rotation_angle,
             unsigned int attack_speed)
    : Object(position, 1.0f, nullptr, rotation_angle),
      attack_speed_(attack_speed),
      range_(1.0) {}

void Tower::Update(types::Time dt, std::list<Enemy>& enemies, std::list<Projectile>& projectiles) {

}

void Tower::Update(types::Time dt, const td::Game&) {}

unsigned int Tower::getAttackSpeed() const { return attack_speed_; }

float Tower::getRange() const { return range_; }

unsigned int Tower::getLevel() const { return level_; }

unsigned int Tower::getMoneySpent() const {
  return money_spent_on_tower_;
}

unsigned int Tower::getCost() const { return cost_; }

unsigned int Tower::getUpgradeCost() const { return upgrade_cost_; }

void Tower::setMoneySpent(unsigned int value) { money_spent_on_tower_ = value; }

const std::string& Tower::getName() const { return name_; }

types::Targeting Tower::getTargeting() const { return targeting_; }

void Tower::setTargeting(types::Targeting targeting) { targeting_ = targeting; }

std::optional<Enemy*> Tower::GetTarget(
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
  types::Position zeroPosition = types::Position(0,0);
  switch (targeting_) {
    case types::kClose: {
      if (enemiesInRange.size() == 0) return std::nullopt;
      std::optional<Enemy*> closestEnemy = {};
      float closest_distance = std::numeric_limits<float>::max();
      for (std::vector<Enemy>::iterator it = enemiesInRange.begin();
           it != enemiesInRange.end(); it++) {
        float distance = EuclideanDistance(it->getPosition(), position_);
        if (distance <= closest_distance) {
          closest_distance = distance;
          closestEnemy = &(*it);
        }
      }
      return closestEnemy;
    }
    case types::kStrong: {
      if (enemiesInRange.size() == 0) return std::nullopt;
      std::optional<Enemy*> strongest_enemy = {};
      float strongest_hp = 0;
      for (std::vector<Enemy>::iterator it = enemiesInRange.begin();
           it != enemiesInRange.end(); it++) {
        float current_health = it->getHealth();
        if (current_health >= strongest_hp) {
          strongest_hp = current_health;
          strongest_enemy = &(*it);
        }
      }
      return strongest_enemy;
    }
    case types::kFirst: {
      if (enemiesInRange.size() == 0) return std::nullopt;
      std::optional<Enemy*> first_enemy = {};
      float furthest_distance = 0;
      for (std::vector<Enemy>::iterator it = enemiesInRange.begin();
           it != enemiesInRange.end(); it++) {
        float current_distance = it->getDistanceMoved();
        if (current_distance >= furthest_distance) {
          furthest_distance = current_distance;
          first_enemy = &(*it);
        }
      }
      return first_enemy;
    }
    case types::kLast: {
      if (enemiesInRange.size() == 0) return std::nullopt;
      std::optional<Enemy*> last_enemy = {};
      float last_distance = std::numeric_limits<float>::max();
      for (std::vector<Enemy>::iterator it = enemiesInRange.begin();
           it != enemiesInRange.end(); it++) {
        float current_distance = it->getDistanceMoved();
        if (current_distance <= last_distance) {
          last_distance = current_distance;
          last_enemy = &(*it);
        }
      }
      return last_enemy;
    }
    case types::kArea:
    return {};
  }
  throw "Target type not recognized";
}

types::Position Tower::GetProjectStartPos() {
  types::Position result;
  result.x =
      position_.x + hitboxRadius_ * cos(rotation_angle_)*0.8f;  // angle in radians
  result.y = position_.y + hitboxRadius_ * sin(rotation_angle_)*0.8f;
  return result;
}
}  // namespace td
