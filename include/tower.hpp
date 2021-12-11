#pragma once

#include <optional>

#include "enemy.hpp"
#include "object.hpp"
#include "projectile.hpp"
#include "types.hpp"

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
        unsigned int attack_speed = 1U, float range = 1.0f,
        unsigned int level = 1, types::Targeting targetTo = types::kFirst);

  void Update(types::Time dt, const td::Game&);

  /// \brief Tower constructor
  /// \param position     Position of the tower
  /// \param attack_speed  Attack speed of the tower
  explicit Tower(types::Position position, float rotation_angle,
                 unsigned int attack_speed);

  /// \brief Get the attack speed of the tower
  /// \return Attack speed of the tower
  virtual unsigned int getAttackSpeed() const;

  /// \brief Get the attack range of the tower
  /// \return Attack range of the tower
  virtual float getRange() const;

  /// \brief Get the level of the tower
  /// \return Level of the tower
  virtual unsigned int getLevel();

  /// \brief Get the upgrade cost of the tower at current level
  /// \return Upgrade cost of the tower
  virtual unsigned int getUpgradeCost() { return 0; };

  /// \brief Get the shooting type of the tower
  /// \return Projectiles shoot by the tower
  /// \param vector vector of the projectiles in current game
  virtual std::vector<Projectile> shoot(std::vector<Projectile> vector,
                                        std::vector<Enemy> enemies) {
    return std::vector<Projectile>{};
  };

  /// \brief Get the target type of the tower
  /// \return Target type of the tower
  virtual char getTargetType();

  /// \brief Set the target type of the tower
  /// \param targetType    Target type of the tower
  virtual void setTargetType(char targetType);

  /// \brief Get the enemy tower is targeting
  /// \return Pointer to the targeted enemy
  /// \param enemies vector of the enemies in current game
  virtual std::optional<const Enemy*> getTarget(
      const std::vector<Enemy>& enemies);

  /// \brief         Calculate the starting position of the projectiles shoot by
  /// the tower
  /// \param centre  Centre position of the tower
  /// \param radius  Radius of the tower (same as hitbox)
  /// \param angle   Angle position of the tower in radians
  types::Position GetProjectStartPos();

 protected:
  unsigned int attack_speed_;        ///< Attack speed of the tower
  float range_;                      ///< Attack range of the tower
  unsigned int level_;               ///< Level of the tower
  char targetTo_;                    ///< Target mode of the tower
  sf::Texture* texture_projectile_;  ///< Pointer to texture of the projectile
                                     ///< the tower shoots
};
}  // namespace td
