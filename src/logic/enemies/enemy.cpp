#include "enemy.hpp"

namespace td
{
    Enemy::Enemy(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float health, int move_speed, 
    float bounty, bool armored, float moved_distance) : Object(position, hitbox, sprite), 
                health_(health), move_speed_(move_speed), bounty_(bounty), armored_(armored), moved_distance_(moved_distance) {}

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
        return move_speed_;
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
        moved_distance_ = distance;
    }

}
