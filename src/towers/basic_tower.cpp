#include "basic_tower.hpp"
#include <SFML/Graphics.hpp>

sf::Vector2<float> position = sf::Vector2<float>(5.0f,5.0f); //putted some random numbers for now

sf::CircleShape hitbox = sf::CircleShape(1.0f, 30UL); //radius, and pointCount

sf::Texture sprite = sf::Texture();   //picture of the tower to here

float rotation_angle = 0.0f;         

unsigned int attack_speed = 10;  //can adjust these later

float range = 10.0f;   

td::Tower basic_tower(position, hitbox, sprite, rotation_angle, attack_speed, range);

