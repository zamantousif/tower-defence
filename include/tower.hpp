#pragma once

#include <optional>

#include "enemy.hpp"
#include "object.hpp"
#include "projectile.hpp"
#include "types.hpp"
#include "collision.hpp"

namespace td {
class Game;
///  \brief Tower class represents the blueprint of a basic tower in the game.
///  The base tower class can be derived further to create towers with special
///  powers.
class Tower : public Object {
 public:
  /// \brief Tower constructor
  /// \param position       Position of the tower
  /// \param hitbox         Radius of the circular region occupied by the tower
  /// \param texture        Texture of the tower
  /// \param attack_speed   Attack speed of the tower
  /// \param range          Attack range of the tower
  /// \param level        Level of the tower
  /// \param targetTo     Stores the target mode of the tower, options: c =
  /// closest, s = strongest or f = furthest travelled
  Tower(types::Position position, float hitbox, sf::Texture* texture,
        sf::Texture* texture_projectile, float rotation_angle = 0.0f,
        unsigned int attack_speed = 1U, float range = 1.0f, unsigned int cost = 0, unsigned int upgrade_cost = 0,
        unsigned int level = 1, types::Targeting targetTo = types::kFirst);

  void Update(types::Time dt, const td::Game&);

  void Update(types::Time dt, std::list<Enemy>& enemies, std::list<Projectile>& projectiles);

  /// \brief Tower constructor
  /// \param position     Position of the tower
  /// \param attack_speed  Attack speed of the tower
  explicit Tower(types::Position position, float rotation_angle,
                 unsigned int attack_speed);

  /// \brief Get the attack speed of the tower
  /// \return Attack speed of the tower
  unsigned int getAttackSpeed() const;

  /// \brief Get the attack range of the tower
  /// \return Attack range of the tower
  float getRange() const;

  /// \brief Get the level of the tower
  /// \return Level of the tower
  unsigned int getLevel() const;

  /// \brief Get the price of the tower
  /// \return Cost of the tower
  unsigned int getCost() const;

  /// \brief Get the total amount of money spent on the tower
  /// \return The total amount of money spent on the tower
  unsigned int getMoneySpent() const;

  /// \brief Set the total amount of money spent on the tower
  /// \param value new value for money_spent_on_tower_
  void setMoneySpent(unsigned int value);

  /// \brief Get the upgrade cost of the tower at current level
  /// \return Upgrade cost of the tower
  unsigned int getUpgradeCost() const;

  /// \brief Get the name of the tower
  /// \return Name of the tower
  const std::string& getName() const;

  /// \brief Get the target type of the tower
  /// \return Target type of the tower
  types::Targeting getTargeting() const;

  /// \brief Set the target type of the tower
  /// \param targetType    Target type of the tower
  void setTargeting(types::Targeting targeting);

  /// \brief Get the shooting type of the tower
  /// \return bool that tells if the tower shot
  /// \param vector vector of the projectiles in current game
  virtual bool shoot(std::vector<Projectile> vector,
                                        std::vector<Enemy> enemies) {
    return false;
  };

  /// \brief Upgrades the tower once
  virtual void Upgrade() { level_++; };

  /// \brief Get the enemy tower is targeting
  /// \return Pointer to the targeted enemy
  /// \param enemies vector of the enemies in current game
  virtual std::optional<Enemy*> GetTarget(
      const std::vector<Enemy>& enemies);

  /// \brief         Calculate the starting position of the projectiles shoot by
  /// the tower
  /// \param centre  Centre position of the tower
  /// \param radius  Radius of the tower (same as hitbox)
  /// \param angle   Angle position of the tower in radians
  types::Position GetProjectStartPos();

 protected:
  std::string name_;                   ///< Name that is used as an identifier
  unsigned int attack_speed_;          ///< Attack speed of the tower
  float range_;                        ///< Attack range of the tower
  unsigned int level_;                 ///< Level of the tower
  types::Targeting targeting_;         ///< Target mode of the tower
  sf::Texture* texture_projectile_;    ///< Pointer to texture of the projectile
                                       ///< the tower shoots
  unsigned int cost_;                  ///< cost of the tower
  unsigned int upgrade_cost_;          ///< upgrade cost of the tower
  unsigned int money_spent_on_tower_;  ///< Total money spent on this tower,
                                       ///< used when selling tower             
};
}  // namespace td
