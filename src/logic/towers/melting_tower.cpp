#include <SFML/Graphics.hpp>
#include "melting_tower.hpp"

namespace td{
  sf::CircleShape hitbox7 = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

  sf::Texture sprite7 = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed7 = 10;  //can adjust these later

  float range7 = 10.0f;   

  unsigned int level7 = 1;

  Melting_tower::Melting_tower(sf::Vector2<float> position, float rotation_angle):
  Tower(position, hitbox7, sprite7, rotation_angle, attack_speed7, range7, level7) {}

   std::vector<projectiles::Projectile> Melting_tower::shoot(std::vector<projectiles::Projectile> vector) 
  {
      //add implementation here
  }

}