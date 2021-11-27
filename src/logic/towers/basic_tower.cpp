#include "basic_tower.hpp"
#include "basic_projectile.hpp"
#include "strong_projectile.hpp"
#include <SFML/Graphics.hpp>

namespace td{
sf::CircleShape hitbox = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

sf::Texture sprite = sf::Texture();   //picture of the tower to here
      
unsigned int attack_speed = 10;  //can adjust these later

float range = 10.0f;   

unsigned int level = 1;

Basic_tower::Basic_tower(sf::Vector2<float> position, float rotation_angle):
Tower(position, hitbox, sprite, rotation_angle, attack_speed, range, level) {}

Projectile Basic_tower::shoot() 
{
  if(level != 4)
  return Basic_projectile(this->getPosition(), this->getRotation()); /// position has to be set to edge of the tower instead of tower centre
  else
   return Strong_projectile(this->getPosition(), this->getRotation()); /// position has to be set to edge of the tower instead of tower centre
}

}