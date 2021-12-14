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

std::optional<Enemy*> Tower::GetTarget(std::vector<Enemy>& enemies) {
  std::vector<Enemy*> enemies_in_range;
  for (Enemy& enemy : enemies) {
    if (IsCircleCollidingWithCircle(position_, range_, enemy.getPosition(), enemy.getHitboxRadius())) {
      enemies_in_range.push_back(&enemy);
    }
  }
  if (enemies_in_range.size() == 0) return std::nullopt;

  //return pointer to correct enemy based on targeting_
  switch (targeting_) {
    case types::kClose: {
      std::optional<Enemy*> closestEnemy = {};
      float closest_distance = std::numeric_limits<float>::max();
      for (Enemy* enemy : enemies_in_range) {
        float distance = EuclideanDistance(enemy->getPosition(), position_);
        if (distance <= closest_distance) {
          closest_distance = distance;
          closestEnemy = enemy;
        }
      }
      return closestEnemy;
    }
    case types::kStrong: {
      std::optional<Enemy*> strongest_enemy = {};
      float strongest_hp = 0;
      for (Enemy* enemy : enemies_in_range) {
        float current_health = enemy->getHealth();
        if (current_health >= strongest_hp) {
          strongest_hp = current_health;
          strongest_enemy = enemy;
        }
      }
      return strongest_enemy;
    }
    case types::kFirst: {
      std::optional<Enemy*> first_enemy = {};
      float furthest_distance = 0;
      for (Enemy* enemy : enemies_in_range) {
        float current_distance = enemy->getDistanceMoved();
        if (current_distance >= furthest_distance) {
          furthest_distance = current_distance;
          first_enemy = enemy;
        }
      }
      return first_enemy;
    }
    case types::kLast: {
      std::optional<Enemy*> last_enemy = {};
      float last_distance = std::numeric_limits<float>::max();
      for (Enemy* enemy : enemies_in_range) {
        float current_distance = enemy->getDistanceMoved();
        if (current_distance <= last_distance) {
          last_distance = current_distance;
          last_enemy = enemy;
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
