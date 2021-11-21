#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <Object.hpp>

TEST(CreateBaseClassObjectAndTestMembers, BaseClassTest)
{
    // Arrange
    sf::CircleShape hitbox;
    hitbox.setRadius(10);
    hitbox.setPointCount(5);
    
    sf::Texture sprite;
    sf::Vector2u dim;
    dim.x = 2U;
    dim.y = 5U;
    sprite.create(dim.x, dim.y);

    sf::Vector2<unsigned int> position;
    position.x = 5U;
    position.y = 6U;
    
    // Act
    td::Object obj(position, hitbox, sprite);

    // Assert
    EXPECT_EQ(obj.getPosition(), position);
    EXPECT_EQ(obj.getHitbox().getRadius(), hitbox.getRadius());
    EXPECT_EQ(obj.getHitbox().getPointCount(), hitbox.getPointCount());
    EXPECT_EQ(obj.getSprite().getSize(), dim);
}
