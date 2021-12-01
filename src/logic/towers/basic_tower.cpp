#include <SFML/Graphics.hpp>
#include "basic_tower.hpp"
#include "basic_projectile.hpp"
#include "strong_projectile.hpp"

namespace td{
  sf::CircleShape hitbox_basic = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

  sf::Texture sprite_basic = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed_basic = 10;  //can adjust these later

  float range_basic = 10.0f;   

  Basic_tower::Basic_tower(sf::Vector2<float> position, float rotation_angle):
  Tower(position, hitbox_basic, sprite_basic, rotation_angle, attack_speed_basic, range_basic) {}

  std::vector<projectiles::Projectile> Basic_tower::shoot(std::vector<projectiles::Projectile> vector) 
  {
    if(this->getLevel() == 1){
      projectiles::Basic_projectile newProjectile = projectiles::Basic_projectile(this->getPosition(), this->getRotation(), 10); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
    else if(this->getLevel() == 2){
      projectiles::Basic_projectile newProjectile = projectiles::Basic_projectile(this->getPosition(), this->getRotation(), 20); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
    else if(this->getLevel() == 3){
      projectiles::Basic_projectile newProjectile = projectiles::Basic_projectile(this->getPosition(), this->getRotation(), 30); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
    else{
      projectiles::Strong_projectile newProjectile = projectiles::Strong_projectile(this->getPosition(), this->getRotation()); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
  }
  }

}