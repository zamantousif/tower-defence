#include "enemy.hpp"

namespace td
{
    Enemy::Enemy(sf::Vector2<float> position, sf::CircleShape hitbox, sf::Texture sprite, float health, int move_speed, 
    float bounty, bool armored, float distance_moved) : Object(position, hitbox, sprite), 
                health_(health), move_speed_(move_speed), bounty_(bounty), armored_(armored), distance_moved_(distance_moved) {}

    float Enemy::getHealth() const
    {
        return health_;
    }

    int Enemy::getMoveSpeed() const
    {
        return move_speed_;
    }
    
    float Enemy::getBounty() const
    {
        return bounty_;
    }

    bool Enemy::isArmored() const
    {
        return armored_;
    }

    float Enemy::getDistanceMoved() const {
      return distance_moved_;
    }

    void Enemy::setDistanceMoved(float distance)
    {
        distance_moved_ = distance;
    }

}
