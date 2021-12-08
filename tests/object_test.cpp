#include "object.hpp"

#include <gtest/gtest.h>

#include "types.hpp"

TEST(CreateBaseClassObjectAndTestGetters, BaseClassTest) {
  // Arrange
  class derived_object : public td::Object {
    void Update(td::types::Time dt) { (void)dt; }
  };
  sf::Texture* pTexture = NULL;

  // Act
  derived_object obj;

  // Assert
  EXPECT_FLOAT_EQ(obj.getPosition().x, 0.0f);
  EXPECT_FLOAT_EQ(obj.getPosition().y, 0.0f);
  EXPECT_FLOAT_EQ(obj.getHitboxRadius(), 0.0f);
  EXPECT_EQ(obj.getTexture(), pTexture);
  EXPECT_EQ(obj.getTexture()->getSize().x, pTexture->getSize().x);
  EXPECT_EQ(obj.getTexture()->getSize().y, pTexture->getSize().x);
  EXPECT_FLOAT_EQ(obj.getRotation(), 0.0f);
}

TEST(CreateBaseClassObjectAndTestSetters, BaseClassTest) {
  // Arrange
  td::types::Position position;
  position.x = 5.9f;
  position.y = 4.2f;
  float rotation_angle = 50.1f;
  // Object is an abstract class; Derive an instance of Object to test it
  class derived_object : public td::Object {
    void Update(td::types::Time dt) { (void)dt; }
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
