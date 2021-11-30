#include <SFML/Graphics.hpp>
#include "slowing_tower.hpp"

namespace td{
  sf::CircleShape hitbox = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

  sf::Texture sprite = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed = 10;  //can adjust these later

  float range = 7.0f;   

  unsigned int level = 1;

  Slowing_tower::Slowing_tower(sf::Vector2<float> position, float rotation_angle):
  Tower(position, hitbox, sprite, rotation_angle, attack_speed, range, level) {}

  std::vector<projectiles::Projectile> Slowing_tower::shoot(std::vector<projectiles::Projectile> vector) 
  {
      //add implementation here
  }

}