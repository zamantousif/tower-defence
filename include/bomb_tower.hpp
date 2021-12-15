#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "tower.hpp"

namespace td {
///  \brief //Implementation of bomb tower that shoots explosive bombs to
///  enemies
class Bomb_tower : public Tower {
 public:
  /// \brief                 Bomb_tower constructor
  /// \param position        Position of the tower
  /// \param rotation_angle  Orientation, in radians of the tower
  Bomb_tower(sf::Vector2<float> position, float rotation_angle = 0.0f,
             sf::Texture* texture = nullptr,
             sf::Texture* texture_projectile = nullptr,
             sf::Texture* texture_explosion = nullptr);

  /// \brief Upgrades the tower once
  void Upgrade();

  /// \brief Run every frame, handles the tower's functionality
  /// \param dt time since last call to this function
  /// \param enemies enemies in the game
  /// \param projectiles projectiles in the game
  void Update(types::Time dt, std::list<Enemy>& enemies, std::list<Projectile>& projectiles);

  /// \brief Add projectiles shoot by the tower to the list of all projectiles
  /// \return List of all projectiles currently in game
  bool Shoot(std::list<Projectile>&, std::list<Enemy>& enemies);

 private:
  sf::Texture* texture_explosion_; ///<Texture of the explosion of the projectile
};
}  // namespace td
