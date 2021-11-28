#include <SFML/Graphics.hpp>
#include "high_damage_tower.hpp"
#include "massive_projectile.hpp"

namespace td{
  sf::CircleShape hitbox4 = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

  sf::Texture sprite4 = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed4 = 10;  //can adjust these later

  float range4 = 10.0f;   

  unsigned int level4 = 1;

  High_damage_tower::High_damage_tower(sf::Vector2<float> position, float rotation_angle):
  Tower(position, hitbox4, sprite4, rotation_angle, attack_speed4, range4, level4) {}

  std::vector<projectiles::Projectile> High_damage_tower::shoot(std::vector<projectiles::Projectile> vector) 
  {
    if(this->getLevel() == 1){
      projectiles::Massive_projectile newProjectile = projectiles::Massive_projectile(this->getPosition(), this->getRotation(), 200); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
      else if(this->getLevel() == 2){
      projectiles::Massive_projectile newProjectile = projectiles::Massive_projectile(this->getPosition(), this->getRotation(), 400); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
       else if(this->getLevel() == 3){
      projectiles::Massive_projectile newProjectile = projectiles::Massive_projectile(this->getPosition(), this->getRotation(), 800); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
      else{
      projectiles::Massive_projectile newProjectile = projectiles::Massive_projectile(this->getPosition(), this->getRotation(), 1300); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
  }

}