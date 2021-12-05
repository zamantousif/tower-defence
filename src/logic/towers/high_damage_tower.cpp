#include "high_damage_tower.hpp"

#include <SFML/Graphics.hpp>

#include "massive_projectile.hpp"


namespace td {
float hitbox_high = 1.0f;  // parameters radius and pointCount

sf::Texture* texture_high = nullptr;  // picture of the tower to here

unsigned int attack_speed_high = 10;  // can adjust these later

float range_high = 10.0f;

char targetTo_high = 's';  // strongest enemy

High_damage_tower::High_damage_tower(sf::Vector2<float> position,
                                     float rotation_angle)
    : Tower(position, hitbox_high, texture_high, rotation_angle,
            attack_speed_high, range_high, targetTo_high) {}

std::list<projectiles::Projectile> High_damage_tower::shoot(
    std::list<projectiles::Projectile> vector) {
  if (this->getLevel() == 1) {
    //    derived_projectile newProjectile =
    //    derived_projectile(this->getTarget(/*vector of enemies
    //    here*/)->getPosition(), this->getRotation(), 200); /// will create
    //    projectile straight on top of targeted enemy
    projectiles::Massive_projectile newProjectile =
        projectiles::Massive_projectile(
            this->getPosition(), this->getRotation(),
            200);  /// position has to be set to edge of the tower instead of
                   /// tower centre
    vector.push_back(newProjectile);
    return vector;
  } else if (this->getLevel() == 2) {
    // projectiles::Massive_projectile newProjectile =
    // projectiles::Massive_projectile(this->getTarget(/*vector of enemies
    // here*/)->getPosition(), this->getRotation(), 400); /// will create
    // projectile straight on top of targeted enemy
    projectiles::Massive_projectile newProjectile =
        projectiles::Massive_projectile(
            this->getPosition(), this->getRotation(),
            400);  /// position has to be set to edge of the tower instead of
                   /// tower centre
    vector.push_back(newProjectile);
    return vector;
  } else if (this->getLevel() == 3) {
    //  projectiles::Massive_projectile newProjectile =
    //  projectiles::Massive_projectile(this->getTarget(/*vector of enemies
    //  here*/)->getPosition(), this->getRotation(), 800); /// will create
    //  projectile straight on top of targeted enemy
    projectiles::Massive_projectile newProjectile =
        projectiles::Massive_projectile(
            this->getPosition(), this->getRotation(),
            800);  /// position has to be set to edge of the tower instead of
                   /// tower centre
    vector.push_back(newProjectile);
    return vector;
  } else {
    //    projectiles::Massive_projectile newProjectile =
    //    projectiles::Massive_projectile(this->getTarget(/*vector of enemies
    //    here*/)->getPosition(), this->getRotation(), 1300); /// will create
    //    projectile straight on top of targeted enemy
    projectiles::Massive_projectile newProjectile =
        projectiles::Massive_projectile(
            this->getPosition(), this->getRotation(),
            1300);  /// position has to be set to edge of the tower instead of
                    /// tower centre
    vector.push_back(newProjectile);
    return vector;
  }
}

}  // namespace td