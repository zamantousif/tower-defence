#pragma once

#include <list>
#include <map>
#include <nlohmann/json.hpp>
#include <vector>

#include "basic_tower.hpp"
#include "bomb_tower.hpp"
#include "enemy.hpp"
#include "high_damage_tower.hpp"
#include "melting_tower.hpp"
#include "projectile.hpp"
#include "slowing_tower.hpp"
#include "tower.hpp"

namespace td {
class Game {
 public:
  /// \brief A default constructor.
  Game();

  /// \return Amount of money the player has
  int getMoney() const;

  /// \return Amount of lives left
  int getLives() const;

  /// \return All the enemies currently on the map
  std::list<Enemy>& getEnemies();
  /// \return All the enemies currently on the (const)
  const std::list<Enemy>& getEnemies() const;

  /// \return All the towers currently on the map
  std::list<Tower>& getTowers();
  /// \return All the towers currently on the map (const)
  const std::list<Tower>& getTowers() const;

  /// \return All the projectiles currently on the map
  std::list<Projectile>& getProjectiles();
  /// \return All the projectiles currently on the map (const)
  const std::list<Projectile>& getProjectiles() const;

  /// \return Whether auto starting rounds is on or not
  bool getAutoStart() const;

  /// \param auto_start Whether auto starting rounds is set on or off
  void setAutoStart(bool auto_start);

  /// \brief Spawn an enemy on the map at the first path vertex.
  ///
  /// The method fails silently if the specified identifier is invalid.
  ///
  /// \param enemy_identifier A unique identifier for the enemy, has to be added
  /// to the game first using the AddEnemy() method.
  ///
  /// \param position The enemy's initial position.
  ///
  /// \return True if the enemy was spawned
  /// successfully, false otherwise.
  bool SpawnEnemy(const std::string& enemy_identifier,
                  types::Position position);
  /// \brief Add a possible enemy to the game.
  ///
  /// If an enemy with the identifier already exists, the method fails silently.
  ///
  /// \param enemy_identifier A unique identifier for the enemy
  ///
  /// \param enemy An enemy instance to add to the game
  ///
  /// \return True if the enemy was added, false otherwise
  bool AddEnemy(const std::string& enemy_identifier, Enemy enemy);

  /// \brief Add a tower onto the map
  /// \param tower The tower to add
  void AddTower(const td::Tower& tower);

  /// \param previous_update If set to true, returns collisions from the
  /// previous update
  ///
  /// \return A map mapping enemies to projectiles that they collide with
  const std::map<Enemy*, Projectile*>& getEnemyCollisions(
      bool previous_update = false);
  /// \param previous_update If set to true, returns collisions from the
  /// previous update
  ///
  /// \return A map mapping projectiles enemies that they
  /// collide with
  const std::map<Projectile*, Enemy*>& getProjectileCollisions(
      bool previous_update = false);

  /// \brief A struct for storing the state of an enemy wave. A round consists
  /// of these waves.
  struct Wave {
    std::string enemy_identifier;
    unsigned int spacing = 500;
    unsigned int offset = 0;
    unsigned int count = 1;

    /// \param enemy_identifier The unique identifier for the enemy that gets
    /// spawned during the wave
    ///
    /// \param spacing The amount of time between enemy
    /// spawns, in milliseconds
    ///
    /// \param offset The amount of time for the wave to
    /// arrive after the round has started, in milliseconds
    ///
    /// \param count The amount of enemies that spawn
    Wave(std::string enemy_identifier, unsigned int spacing,
         unsigned int offset, unsigned int count)
        : enemy_identifier(enemy_identifier),
          spacing(spacing),
          offset(offset),
          count(count) {}
  };

  /// \brief Upgrades the tower given as the parameter if the player has enough
  /// money \param tower The tower being upgraded
  void UpgradeTower(Tower* tower);

  /// \brief Sells the tower given as a parameter, deleting it and adding money
  /// to the player's balance \param tower The tower being sold
  void SellTower(Tower* tower);

  /// \brief Begins the buying process by returning the appropriate tower to
  /// application if the player has enough money \param name Identifier used to
  /// map to a tower object \param tower_texture Pointer to the texture of the
  /// tower \param projectile_texture Pointer to the texture of the projectile
  Tower StartBuyingTower(std::string name, sf::Texture* tower_texture,
                         sf::Texture* projectile_texture);

  /// \return A vector of rounds, with each round being a vector consisting of
  /// Game::Wave elements (waves)
  const std::vector<std::vector<Wave>>& getRounds();

  /// \brief Adds rounds from a JSON file. Doesn't remove pre-existing rounds.
  ///
  /// The JSON file consists of an array of arrays that all contain an object of
  /// the form
  /// { "enemyIdentifier": "asd", "spacing": 500, "offset": 0, "count": 5}
  void LoadRounds(const std::string& file_path);

 private:
  int money_ = 2000;
  int lives_ = 100;
  std::list<Enemy> enemies_;
  std::list<Tower> towers_;
  std::list<Projectile> projectiles_;
  std::map<Enemy*, Projectile*> enemy_collisions_;
  std::map<Enemy*, Projectile*> previous_enemy_collisions_;
  std::map<Projectile*, Enemy*> projectile_collisions_;
  std::map<Projectile*, Enemy*> previous_projectile_collisions_;
  std::map<std::string, Enemy> enemy_table_;
  std::vector<std::vector<Wave>> rounds_;
  bool auto_start_;  ///<whether rounds start automatically or not
};
}  // namespace td
