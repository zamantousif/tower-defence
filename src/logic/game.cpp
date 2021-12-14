#include "game.hpp"

#include <fstream>

#include "collision.hpp"

// TODO: Clean up the smaller constructor

namespace td {
Game::Game(Map* map, const std::string& round_file_path, int starting_money,
           int starting_lives,
           const std::map<std::string, sf::Texture*>& textures)
    : map_(map),
      money_(starting_money),
      lives_(starting_lives),
      round_in_progress_(false),
      current_round_index_(0) {
  LoadEnemies(textures);
  LoadRounds(round_file_path);
}
Game::Game(Map* map, const std::string& round_file_path,
           const std::map<std::string, sf::Texture*>& textures)
    : map_(map),
      money_(2000),
      lives_(100),
      round_in_progress_(false),
      current_round_index_(0) {
  LoadEnemies(textures);
  LoadRounds(round_file_path);
}

int Game::getMoney() const { return money_; }

int Game::getLives() const { return lives_; }

void Game::Update() {
  sf::Time dt = update_clock_.getElapsedTime();
  sf::Time round_time = round_clock_.getElapsedTime();
  update_clock_.restart();

  // Iterate through the current waves, spawning enemies as necessary
  for (Wave& wave : rounds_[current_round_index_]) {
    if (wave.last_spawn_time.asMilliseconds() +
                static_cast<sf::Int32>(wave.spacing) >=
            round_time.asMilliseconds() &&
        wave.enemies_spawned < wave.count) {
      wave.enemies_spawned++;
      SpawnEnemy(wave.enemy_identifier, map_->GetStartingPosition());
      wave.last_spawn_time = round_time;
    }
  }

  // Iterate through all the enemies, calling their Update method and updating
  // the collision tables
  for (Enemy& enemy : enemies_) {
    // Call the Update method for every enemy
    enemy.Update(dt, map_->getEnemyPath());

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

void Game::AddTower(const td::Tower& tower) { towers_.push_back(tower); }

const std::map<const Projectile*, std::vector<const Enemy*>>&
Game::getProjectileCollisions(bool previous_update) {
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

  for (auto& round_raw : json) {
    std::vector<Wave> round;
    for (auto& wave_raw : round_raw) {
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
                             textures.at("cockroach"), 200, 100, 10, false, 0));
  enemy_table_.emplace("fly", Enemy(td::types::Position(0, 0), 40.0f,
                                    textures.at("fly"), 150, 200, 14, false, 0));
  enemy_table_.emplace(
      "beetle", Enemy(td::types::Position(0, 0), 60.0f, textures.at("beetle"),
                      300, 10, 20, true, 0));
  enemy_table_.emplace("dragonfly",
                       Enemy(td::types::Position(0, 0), 80.0f,
                             textures.at("dragonfly"), 4000, 100, 400, true, 0));
}

bool Game::CheckTowerPlacementCollision(const Tower& tower) {
  std::vector<td::types::Position> polygon_points;
  // Check collision with blocked regions on the map
  for (auto& region : map_->getBlockedRegions()) {
    for (size_t index = 0; index != region.getPointCount(); index++) {
      polygon_points.emplace_back(region.getPoint(index));
    }
    if (IsCircleCollidingWithPolygon(tower.getPosition(),
                                     tower.getHitboxRadius(), polygon_points))
      return true;
  }
  // Check collision with existing towers on the map
  for (auto& existing_tower : towers_) {
    if (IsCircleCollidingWithCircle(
            tower.getPosition(), tower.getHitboxRadius(),
            existing_tower.getPosition(), existing_tower.getHitboxRadius()))
      return true;
  }
  // Check collision with boundary of the map
  std::vector<std::pair<td::types::Position, td::types::Position>> window_edges;
  sf::Vector2f corner1 = sf::Vector2f(0.0f, 0.0f);
  sf::Vector2f corner2 = sf::Vector2f(1520.0f, 0.0f);
  sf::Vector2f corner3 = sf::Vector2f(1520.0f, 1080.0f);
  sf::Vector2f corner4 = sf::Vector2f(0.0f, 1080.0f);
  window_edges.emplace_back(corner1, corner2);
  window_edges.emplace_back(corner2, corner3);
  window_edges.emplace_back(corner3, corner4);
  window_edges.emplace_back(corner4, corner1);
  for (auto& edge : window_edges) {
    if (IsCircleIntersectingPolygonEdge(tower.getPosition(),
                                        tower.getHitboxRadius(), edge))
      return true;
  }

  // Otherwise return false, if no collisions
  return false;
}

void Game::StartRound(size_t round_index) {
  round_in_progress_ = true;
  current_round_index_ = round_index;
  round_clock_.restart();
}

bool Game::IsRoundInProgress() { return round_in_progress_; }

const Map* Game::getMap() const { return map_; }

Map* Game::getMap() { return map_; }

size_t Game::getCurrentRoundIndex() { return current_round_index_; }

}  // namespace td
