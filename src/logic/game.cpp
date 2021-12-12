#include "game.hpp"

#include <fstream>

namespace td {
Game::Game(Map* map, int starting_money, int starting_lives)
    : map_(map), money_(starting_money), lives_(starting_lives) {}
Game::Game(Map* map) : map_(map), money_(2000), lives_(100) {}

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

void Game::AddTower(const td::Tower& tower) { towers_.push_back(tower); }

const std::map<Projectile*, Enemy*>& Game::getProjectileCollisions(
    bool previous_update) {
  if (previous_update) {
    return previous_projectile_collisions_;
  } else {
    return projectile_collisions_;
  }
}

void Game::UpgradeTower(Tower* tower) {
  if (tower->getLevel() < 4 && (int)tower->getUpgradeCost() <= money_) {
    money_ -= tower->getUpgradeCost();
    tower->setMoneySpent(tower->getUpgradeCost() + tower->getMoneySpent());
    tower->Upgrade();
  }
}

void Game::SellTower(Tower* tower) {
  // 0.75 is a factor of how much money you get back when selling
  money_ += static_cast<int>(tower->getMoneySpent() * 0.75);
  // TODO: delete tower here
}

Tower Game::StartBuyingTower(
    std::string name, sf::Texture* tower_texture,
    sf::Texture* projectile_texture) {  // TODO: check money
  if (name == "basic_tower") {
    return Basic_tower(types::Position(0, 0), 0.0f, tower_texture,
                       projectile_texture);
  } else if (name == "bomb_tower") {
    return Bomb_tower(types::Position(0, 0), 0.0f, tower_texture,
                      projectile_texture);
  } else if (name == "slowing_tower") {
    return Slowing_tower(types::Position(0, 0), 0.0f, tower_texture);
  } else if (name == "thorn_eruptor") {
    return Basic_tower(types::Position(0, 0), 0.0f, tower_texture,
                       projectile_texture);
  } else if (name == "sniper_tower") {
    return High_damage_tower(types::Position(0, 0), 0.0f, tower_texture,
                             projectile_texture);
  } else if (name == "melting_tower") {
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

const Map* Game::getMap() const { return map_; }

Map* Game::getMap() { return map_; }

}  // namespace td
