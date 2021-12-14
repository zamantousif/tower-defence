#include "game.hpp"

#include <fstream>
#include <iostream>  //TODO: temporary

#include "collision.hpp"
#include "constants.hpp"

namespace td {
Game::Game(Map* map, int starting_money, int starting_lives,
           const std::map<std::string, sf::Texture*>& textures)
    : map_(map), money_(starting_money), lives_(starting_lives) {
  LoadEnemies(textures);
}
Game::Game(Map* map, const std::map<std::string, sf::Texture*>& textures)
    : map_(map), money_(2000), lives_(100) {
  LoadEnemies(textures);
}

int Game::getMoney() const { return money_; }

int Game::getLives() const { return lives_; }

void Game::Update(types::Time dt) {
  // Iterate through all the enemies, calling their Update method and updating
  // the collision tables
  for (Enemy& enemy : enemies_) {
    // Call the Update method for every enemy
    enemy.Update(dt, *this);

    // Projectiles that the enemy collided with in the previous frame
    auto enemy_collided_with = enemy_collisions_.find(&enemy);
    if (enemy_collided_with != enemy_collisions_.end()) {
      previous_enemy_collisions_[&enemy] = enemy_collided_with->second;
    }

    std::map<const Enemy*, std::vector<const Projectile*>> new_enemy_collisions;

    for (const Projectile& projectile : projectiles_) {
      // Check if Projectile collides with the Enemy
      if (IsCircleCollidingWithCircle(
              projectile.getPosition(), projectile.getHitboxRadius(),
              enemy.getPosition(), enemy.getHitboxRadius())) {
        auto collisions = new_enemy_collisions.find(&enemy);
        if (collisions != new_enemy_collisions.end()) {
          collisions->second.push_back(&projectile);
        } else {
          new_enemy_collisions[&enemy] = {&projectile};
        }
      }
    }
  }

  // Iterate through all the projectiles, calling their Update method and
  // updating the collision tables
  for (Projectile& projectile : projectiles_) {
    // Call the Update method for every projectile
    projectile.Update(dt, *this);

    // Enemies that the projectile collided with in the previous frame
    auto projectile_collided_with = projectile_collisions_.find(&projectile);
    if (projectile_collided_with != projectile_collisions_.end()) {
      previous_projectile_collisions_[&projectile] =
          projectile_collided_with->second;
    }

    std::map<const Projectile*, std::vector<const Enemy*>>
        new_projectile_collisions;

    for (const Enemy& enemy : enemies_) {
      // Check if Enemy collides with the Projectile
      if (IsCircleCollidingWithCircle(
              projectile.getPosition(), projectile.getHitboxRadius(),
              enemy.getPosition(), enemy.getHitboxRadius())) {
        auto collisions = new_projectile_collisions.find(&projectile);
        if (collisions != new_projectile_collisions.end()) {
          collisions->second.push_back(&enemy);
        } else {
          new_projectile_collisions[&projectile] = {&enemy};
        }
      }
    }
  }
}

const std::list<Enemy>& Game::getEnemies() const { return enemies_; }
std::list<Enemy>& Game::getEnemies() { return enemies_; }

const std::list<Tower>& Game::getTowers() const { return towers_; }
std::list<Tower>& Game::getTowers() { return towers_; }

const std::list<Projectile>& Game::getProjectiles() const {
  return projectiles_;
}
std::list<Projectile>& Game::getProjectiles() { return projectiles_; }

bool Game::getAutoStart() const { return auto_start_; }

void Game::setAutoStart(bool auto_start) { auto_start_ = auto_start; }

bool Game::SpawnEnemy(const std::string& enemy_identifier,
                      types::Position position) {
  try {
    Enemy enemy_copy = enemy_table_.at(enemy_identifier);
    enemy_copy.setPosition(position);
    enemies_.push_back(enemy_copy);
    return true;
  } catch (std::out_of_range e) {
    return false;
  }
}

bool Game::AddEnemy(const std::string& enemy_identifier, Enemy enemy) {
  return enemy_table_.emplace(enemy_identifier, enemy).second;
}

const std::map<const Enemy*, std::vector<const Projectile*>>&
Game::getEnemyCollisions(bool previous_update) {
  if (previous_update) {
    return previous_enemy_collisions_;
  } else {
    return enemy_collisions_;
  }
}

void Game::AddTower(td::Tower& tower) {
  unsigned int cost = tower.getCost();
  money_ -= cost;
  tower.setMoneySpent(cost);
  towers_.push_back(tower);
}

const std::map<const Projectile*, std::vector<const Enemy*>>&
Game::getProjectileCollisions(bool previous_update) {
  if (previous_update) {
    return previous_projectile_collisions_;
  } else {
    return projectile_collisions_;
  }
}

void Game::UpgradeTower(Tower* tower) {
  if (tower->getLevel() < 4 && tower->getUpgradeCost() <= money_) {
    money_ -= tower->getUpgradeCost();
    tower->setMoneySpent(tower->getUpgradeCost() + tower->getMoneySpent());

    if (tower->getName() == "basic_tower") {
      Basic_tower* casted_tower = static_cast<Basic_tower*>(tower);
      casted_tower->Basic_tower::Upgrade();
    } else if (tower->getName() == "bomb_tower") {
      Bomb_tower* casted_tower = static_cast<Bomb_tower*>(tower);
      casted_tower->Bomb_tower::Upgrade();
    } else if (tower->getName() == "sniper_tower") {
      High_damage_tower* casted_tower = static_cast<High_damage_tower*>(tower);
      casted_tower->High_damage_tower::Upgrade();
    } else if (tower->getName() == "melting_tower") {
      Melting_tower* casted_tower = static_cast<Melting_tower*>(tower);
      casted_tower->Melting_tower::Upgrade();
    } else if (tower->getName() == "slowing_tower") {
      Slowing_tower* casted_tower = static_cast<Slowing_tower*>(tower);
      casted_tower->Slowing_tower::Upgrade();
    } else if (tower->getName() == "thorn_eruptor") {
      ThornEruptor* casted_tower = static_cast<ThornEruptor*>(tower);
      casted_tower->ThornEruptor::Upgrade();
    } else {
      tower->Upgrade();
    }
  }
}

void Game::SellTower(Tower* tower) {
  money_ += static_cast<int>(
      tower->getMoneySpent() * 3 /
      4);  // 3/4 is a factor of how much money you get back when selling
  // TODO: mark tower for removal here
}

Tower Game::StartBuyingTower(std::string name, sf::Texture* tower_texture,
                             sf::Texture* projectile_texture) {
  if (name == "basic_tower" && money_ >= kCostBasicTower) {
    return Basic_tower(types::Position(0, 0), 0.0f, tower_texture,
                       projectile_texture);
  } else if (name == "bomb_tower" && money_ >= kCostBombTower) {
    return Bomb_tower(types::Position(0, 0), 0.0f, tower_texture,
                      projectile_texture);
  } else if (name == "slowing_tower" && money_ >= kCostSlowingTower) {
    return Slowing_tower(types::Position(0, 0), 0.0f, tower_texture);
  } else if (name == "thorn_eruptor" && money_ >= kCostThornEruptor) {
    return ThornEruptor(types::Position(0, 0), 0.0f, tower_texture,
                        projectile_texture);
  } else if (name == "sniper_tower" && money_ >= kCostHighDamageTower) {
    return High_damage_tower(types::Position(0, 0), 0.0f, tower_texture,
                             projectile_texture);
  } else if (name == "melting_tower" && money_ >= kCostMeltingTower) {
    return Melting_tower(types::Position(0, 0), 0.0f, tower_texture);
  }
  return Basic_tower(types::Position(0, 0), 0, nullptr, nullptr);
}

const std::vector<std::vector<Game::Wave>>& Game::getRounds() {
  return rounds_;
}

void Game::LoadRounds(const std::string& file_path) {
  std::ifstream json_file = std::ifstream(file_path);
  nlohmann::json json;
  json_file >> json;

  for (auto round_raw : json) {
    std::vector<Wave> round;
    for (auto wave_raw : round_raw) {
      round.push_back(Wave(wave_raw.at("enemyIdentifier"),
                           wave_raw.at("spacing"), wave_raw.at("offset"),
                           wave_raw.at("count")));
    }
    rounds_.push_back(round);
  }
}

void Game::LoadEnemies(const std::map<std::string, sf::Texture*>& textures) {
  enemy_table_.emplace("cockroach",
                       Enemy(td::types::Position(0, 0), 40.0f,
                             textures.at("cockroach"), 200, 10, 10, false, 0));
  enemy_table_.emplace("fly", Enemy(td::types::Position(0, 0), 40.0f,
                                    textures.at("fly"), 150, 20, 14, false, 0));
  enemy_table_.emplace(
      "beetle", Enemy(td::types::Position(0, 0), 60.0f, textures.at("beetle"),
                      300, 10, 20, true, 0));
  enemy_table_.emplace("dragonfly",
                       Enemy(td::types::Position(0, 0), 80.0f,
                             textures.at("dragonfly"), 4000, 10, 400, true, 0));
}

bool Game::CheckTowerPlacementCollision(const Tower& tower) {
  std::vector<td::types::Position> polygon_points;
  // Check collision with blocked regions on the map
  for (auto& region : map_->getBlockedRegions()) {
    polygon_points.clear();
    for (size_t index = 0; index < region.getPointCount(); index++) {
      polygon_points.emplace_back(region.getPoint(index));
    }
    if (IsCircleCollidingWithPolygon(tower.getPosition(),
                                     tower.getHitboxRadius(), polygon_points)) {
      return true;
    }
  }
  // Check collision with existing towers on the map
  for (auto& existing_tower : towers_) {
    if (IsCircleCollidingWithCircle(
            tower.getPosition(), tower.getHitboxRadius(),
            existing_tower.getPosition(), existing_tower.getHitboxRadius())) {
      return true;
    }
  }
  // Check collision with boundary of the map
  std::vector<std::pair<td::types::Position, td::types::Position>> window_edges;
  sf::Vector2f corner1 = sf::Vector2f(0.0f, 0.0f);
  sf::Vector2f corner2 = sf::Vector2f(1520.0f, 0.0f);
  sf::Vector2f corner3 = sf::Vector2f(1520.0f, 1080.0f);
  sf::Vector2f corner4 = sf::Vector2f(0.0f, 1080.0f);
  std::pair<td::types::Position, td::types::Position> top, bottom, left, right;
  top = std::make_pair(corner1, corner2);
  right = std::make_pair(corner2, corner3);
  bottom = std::make_pair(corner3, corner4);
  left = std::make_pair(corner4, corner1);
  window_edges = {top, right, bottom, left};
  for (auto& edge : window_edges) {
    if (IsCircleIntersectingLineSegment(tower.getPosition(),
                                        tower.getHitboxRadius(), edge)) {
      return true;
    }
  }
  // Otherwise return false, if no collisions
  return false;
}

const Map* Game::getMap() const { return map_; }

Map* Game::getMap() { return map_; }

}  // namespace td
