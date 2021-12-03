#include <SFML/Graphics.hpp>
#include "melting_tower.hpp"

namespace td{
  float hitbox_melting = 1.0f; //parameters radius and pointCount

  sf::Texture sprite_melting = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed_melting = 10;  //can adjust these later

  float range_melting = 10.0f;   

  Melting_tower::Melting_tower(sf::Vector2<float> position, float rotation_angle):
  Tower(position, hitbox_melting, sprite_melting, rotation_angle, attack_speed_melting, range_melting) {}

   std::vector<projectiles::Projectile> Melting_tower::shoot(std::vector<projectiles::Projectile> vector) 
  {
      //add implementation here
  }

}