#include <SFML/Graphics.hpp>
#include "bomb_tower.hpp"
#include "bomb_projectile.hpp"

namespace td{
  sf::CircleShape hitbox8 = sf::CircleShape(1.0f, 30UL); //parameters radius and pointCount

  sf::Texture sprite8 = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed8 = 10;  //can adjust these later

  float range8 = 10.0f;   

  unsigned int level8 = 1;

  Bomb_tower::Bomb_tower(sf::Vector2<float> position, float rotation_angle):
  Tower(position, hitbox8, sprite8, rotation_angle, attack_speed8, range8, level8) {}

  std::vector<projectiles::Projectile> Bomb_tower::shoot(std::vector<projectiles::Projectile> vector)
  {
     if(this->getLevel() == 1){
      projectiles::Bomb_projectile newProjectile = projectiles::Bomb_projectile(this->getPosition(), this->getRotation(), 15); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
      else if(this->getLevel() == 2){
      projectiles::Bomb_projectile newProjectile = projectiles::Bomb_projectile(this->getPosition(), this->getRotation(), 30); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
      else if(this->getLevel() == 3){
      projectiles::Bomb_projectile newProjectile = projectiles::Bomb_projectile(this->getPosition(), this->getRotation(), 45); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
      else{
      projectiles::Bomb_projectile newProjectile = projectiles::Bomb_projectile(this->getPosition(), this->getRotation(), 60); /// position has to be set to edge of the tower instead of tower centre
      vector.push_back(newProjectile);
      return vector;
    }
  }

}