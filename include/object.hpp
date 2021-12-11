#pragma once

#include "types.hpp"

namespace td {
class Game;
///  \brief Object class is an abstract class representing the basic entity of
///  the game. The object class shall be inherited by all other game entities
///  such as towers, enemies, etc.
class Object {
 public:
  /// \brief Object constructor
  /// \param position       Position of the object
  /// \param hitboxRadius   Radius of the circular region occupied by the object
  /// \param texture        Texture of the object
  /// \param rotation_angle Orientation, in radians of the object
  Object(types::Position position = types::Position(0.0f, 0.0f),
         float hitboxRadius = 0.0f, sf::Texture* texture = nullptr,
         float rotation_angle = 0.0f);

  /// \brief Update the state of the object
  /// \param dt Delta time, time elapsed since last update
  virtual void Update(types::Time dt, const td::Game&) = 0;

  /// \brief Get the position of the object
  /// \return Position of the object
  virtual types::Position getPosition() const;

  /// \brief Get the radius of circular region occupied by the object
  /// \return Radius of the circular region occupied by the object
  virtual float getHitboxRadius() const;

  /// \brief Get a const pointer to the texture of the object
  /// \return Texture of the object
  virtual const sf::Texture* getTexture() const;

  /// \brief Get a pointer to the texture of the object
  /// \return Texture of the object
  virtual sf::Texture* getTexture();

  /// \brief Set the position of the object
  /// \param position Position of the object
  virtual void setPosition(types::Position position);

  /// \brief Set the rotation of the object
  /// \param angle  Orientation of the object
  virtual void setRotation(float angle);

  /// \brief Get the orientation of the object
  /// \return Orientation, in radians of the object
  virtual float getRotation() const;

 protected:
  types::Position position_;  ///< Position of the object
  float
      hitboxRadius_;  ///< Radius of the circular region occupied by the object
  sf::Texture* texture_;  ///< Texture of the object
  float rotation_angle_;  ///< Orientation, in radians of the object
};
}  // namespace td
