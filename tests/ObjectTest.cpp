#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <Object.hpp>

TEST(CreateBaseClassObjectAndTestMembers, BaseClassTest)
{
    // Arrange
    sf::Vector2<float> position;
    position.x = 5.0f;
    position.y = 6.0f;

    sf::CircleShape hitbox;
    hitbox.setRadius(10);
    hitbox.setPointCount(5);
    
    sf::Texture sprite;
    // NOTE Dimension declared as sf::Vector2u which is the type returned by sf::Texture::getSize()
    sf::Vector2u dim;
    dim.x = 2U;
    dim.y = 5U;
    sprite.create(dim.x, dim.y);
    
    // Act
    td::Object obj(position, hitbox, sprite);

    // Assert
    EXPECT_FLOAT_EQ(obj.getPosition().x, position.x);
    EXPECT_FLOAT_EQ(obj.getPosition().y, position.y);
    EXPECT_EQ(obj.getHitbox().getRadius(), hitbox.getRadius());
    EXPECT_EQ(obj.getHitbox().getPointCount(), hitbox.getPointCount());
    EXPECT_EQ(obj.getSprite().getSize(), dim);
}
