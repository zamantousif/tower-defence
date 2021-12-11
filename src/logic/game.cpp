#include "game.hpp"

#include <fstream>

namespace td {
Game::Game() {}

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
      if (true) {
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

    std::map<const Projectile*, std::vector<const Enemy*>> new_projectile_collisions;

    for (const Enemy& enemy : enemies_) {
      // Check if Enemy collides with the Projectile
      if (true) {
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

const std::map<const Enemy*, std::vector<const Projectile*>>& Game::getEnemyCollisions(
    bool previous_update) {
  if (previous_update) {
    return previous_enemy_collisions_;
  } else {
    return enemy_collisions_;
  }
}

const std::map<const Projectile*, std::vector<const Enemy*>>& Game::getProjectileCollisions(
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
