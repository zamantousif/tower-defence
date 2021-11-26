#include "basic_tower.hpp"
#include <SFML/Graphics.hpp>

namespace td{
sf::CircleShape hitbox = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

sf::Texture sprite = sf::Texture();   //picture of the tower to here
      
unsigned int attack_speed = 10;  //can adjust these later

float range = 10.0f;   

Basic_tower::Basic_tower(sf::Vector2<float> position, float rotation_angle):
Tower(position, hitbox, sprite, rotation_angle, attack_speed, range) {}

Projectile Basic_tower::shoot() 
{
   // return basic_projectile
}

}