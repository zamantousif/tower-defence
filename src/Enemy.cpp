#include "Enemy.hpp"

namespace td
{
    Enemy::Enemy(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float health, int moveSpeed, 
    float bounty, bool armored, float movedDistance) : Object(position, hitbox, sprite), 
                health_(health), moveSpeed_(moveSpeed), bounty_(bounty), armored_(armored), movedDistance_(movedDistance) {}

    sf::Vector2<float> Enemy::getPosition()
    {
        return position_;
    }

    float Enemy::getHealth()
    {
        return health_;
    }

    int Enemy::getMoveSpeed()
    {
        return moveSpeed_;
    }

    void Enemy::doUponDeath()
    {
        // do something upon death such as spawing other objects/enemies
    }
    
    float Enemy::getBounty()
    {
        return bounty_;
    }

    bool Enemy::isArmored()
    {
        return armored_;
    }

    void Enemy::setDistanceMoved(float distance)
    {
        movedDistance_ = distance;
    }

}
