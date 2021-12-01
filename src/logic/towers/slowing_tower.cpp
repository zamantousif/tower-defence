#include <SFML/Graphics.hpp>
#include "slowing_tower.hpp"

namespace td{
     sf::CircleShape hitbox_slowing = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

  sf::Texture sprite_slowing = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed_slowing = 10;  //can adjust these later

  float range_slowing = 7.0f;   

  Slowing_tower::Slowing_tower(sf::Vector2<float> position, float rotation_angle):
  Tower(position, hitbox_slowing, sprite_slowing, rotation_angle, attack_speed_slowing, range_slowing) {}

  std::vector<projectiles::Projectile> Slowing_tower::shoot(std::vector<projectiles::Projectile> vector) 
  {
      //add implementation here
  }

}