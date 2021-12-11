#include "game.hpp"

#include <fstream>

namespace td {
Game::Game() {}

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

const std::map<Projectile*, Enemy*>& Game::getProjectileCollisions(
    bool previous_update) {
  if (previous_update) {
    return previous_projectile_collisions_;
  } else {
    return projectile_collisions_;
  }
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

}  // namespace td
