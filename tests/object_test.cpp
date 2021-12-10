#include "object.hpp"

#include "gtest/gtest.h"
#include "types.hpp"

namespace td {
namespace test {
// The fixture for testing class Object.
class ObjectTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  ObjectTest() {
    // You can do set-up work for each test here.
  }

  ~ObjectTest() override {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for ObjectTest.
};

TEST_F(ObjectTest, CreateBaseClassObjectAndTestGetters) {
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
  EXPECT_FLOAT_EQ(obj.getRotation(), 0.0f);
}

TEST_F(ObjectTest, CreateBaseClassObjectAndTestSetters) {
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

}  // namespace test
}  // namespace td
