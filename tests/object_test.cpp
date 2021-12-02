#include "object.hpp"

#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>

TEST(CreateBaseClassObjectAndTestGetters, BaseClassTest) {
  // Arrange
  class derived_object : public td::Object {
    void Update(sf::Time dt) { (void)dt; }
  };

  // Act
  derived_object obj;

  // Assert
  EXPECT_FLOAT_EQ(obj.getPosition().x, 0.0f);
  EXPECT_FLOAT_EQ(obj.getPosition().y, 0.0f);
  EXPECT_FLOAT_EQ(obj.getHitbox().getRadius(), 0.0f);
  EXPECT_EQ(obj.getHitbox().getPointCount(), 30UL);
  EXPECT_EQ(obj.getSprite().getSize().x, 0U);
  EXPECT_EQ(obj.getSprite().getSize().y, 0U);
  EXPECT_FLOAT_EQ(obj.getRotation(), 0.0f);
}

TEST(CreateBaseClassObjectAndTestSetters, BaseClassTest) {
  // Arrange
  sf::Vector2f position;
  position.x = 5.9f;
  position.y = 4.2f;
  float rotation_angle = 50.1f;
  // Object is an abstract class; Derive an instance of Object to test it
  class derived_object : public td::Object {
    void Update(sf::Time dt) { (void)dt; }
  };

  // Act
  derived_object obj;
  obj.setPosition(position);
  obj.setRotation(rotation_angle);

  // Assert
  EXPECT_FLOAT_EQ(obj.getPosition().x, position.x);
  EXPECT_FLOAT_EQ(obj.getPosition().y, position.y);
  EXPECT_FLOAT_EQ(obj.getRotation(), rotation_angle);
}
