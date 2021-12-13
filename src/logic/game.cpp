#include "game.hpp"

#include <fstream>
#include "constants.hpp"
#include <iostream> //TODO: temporary

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

const std::map<Enemy*, Projectile*>& Game::getEnemyCollisions(
    bool previous_update) {
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

const std::map<Projectile*, Enemy*>& Game::getProjectileCollisions(
    bool previous_update) {
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
    
    Basic_tower* casted_tower = dynamic_cast<Basic_tower*>(tower);
    Bomb_tower* casted_tower2 = dynamic_cast<Bomb_tower*>(tower);
    High_damage_tower* casted_tower3 = dynamic_cast<High_damage_tower*>(tower);
    Melting_tower* casted_tower4 = dynamic_cast<Melting_tower*>(tower);
    Slowing_tower* casted_tower5 = dynamic_cast<Slowing_tower*>(tower);
    std::cout << "checking cast" << std::endl;
    if (casted_tower) {
      std::cout << "yippee1" << std::endl;
      casted_tower->Basic_tower::Upgrade();
    } else if (casted_tower2) {
      std::cout << "yippee2" << std::endl;
      casted_tower2->Upgrade();
    } else if (casted_tower3) {
      std::cout << "yippee3" << std::endl;
      casted_tower3->Upgrade();
    } else if (casted_tower4) {
      std::cout << "yippee4" << std::endl;
      casted_tower4->Upgrade();
    } else if (casted_tower5) {
      std::cout << "yippee5" << std::endl;
      casted_tower5->Upgrade();
    } else {
      tower->Upgrade();
    }
    
  }
}

void Game::SellTower(Tower* tower) {
  money_ += static_cast<int>(tower->getMoneySpent()*3/4); // 3/4 is a factor of how much money you get back when selling
  //TODO: mark tower for removal here
}

Tower Game::StartBuyingTower(
    std::string name, sf::Texture* tower_texture,
    sf::Texture* projectile_texture) {  // TODO: check money
  if (name == "basic_tower" && money_ >= kCostBasicTower) {
    return Basic_tower(types::Position(0, 0), 0.0f, tower_texture,
                       projectile_texture);
  } else if (name == "bomb_tower" && money_ >= kCostBombTower) {
    return Bomb_tower(types::Position(0, 0), 0.0f, tower_texture,
                      projectile_texture);
  } else if (name == "slowing_tower" && money_ >= kCostSlowingTower) {
    return Slowing_tower(types::Position(0, 0), 0.0f, tower_texture);
  } else if (name == "thorn_eruptor" && money_ >= kCostThornEruptor) {
    return Basic_tower(types::Position(0, 0), 0.0f, tower_texture,
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
  // Check collision with blocked regions
  for (auto& region : map_->getBlockedRegions()) {
    for (size_t index = 0; index != region.getPointCount(); index++) {
      polygon_points.emplace_back(region.getPoint(index));
    }
    if (IsCircleCollidingWithPolygon(tower.getPosition(),
                                     tower.getHitboxRadius(), polygon_points))
      return true;
  }
  return false;
}

const Map* Game::getMap() const { return map_; }

Map* Game::getMap() { return map_; }

}  // namespace td
