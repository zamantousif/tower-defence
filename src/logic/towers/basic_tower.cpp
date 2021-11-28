#include <SFML/Graphics.hpp>
#include "basic_tower.hpp"
#include "basic_projectile.hpp"
#include "strong_projectile.hpp"

namespace td{
  sf::CircleShape hitbox3 = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

  sf::Texture sprite3 = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed3 = 10;  //can adjust these later

  float range3 = 10.0f;   

  unsigned int level3 = 1;

  Basic_tower::Basic_tower(sf::Vector2<float> position, float rotation_angle):
  Tower(position, hitbox3, sprite3, rotation_angle, attack_speed3, range3, level3) {}

  std::vector<Projectile> Basic_tower::shoot(std::vector<Projectile> vector) 
  {
    if(level3 == 1){
      Basic_projectile newProjectile = Basic_projectile(this->getPosition(), this->getRotation(), 10); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
    else if(level3 == 2){
      Basic_projectile newProjectile = Basic_projectile(this->getPosition(), this->getRotation(), 20); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
    else if(level3 == 3){
      Basic_projectile newProjectile = Basic_projectile(this->getPosition(), this->getRotation(), 20); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
    else{
      Strong_projectile newProjectile = Strong_projectile(this->getPosition(), this->getRotation()); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
  }
  }

}