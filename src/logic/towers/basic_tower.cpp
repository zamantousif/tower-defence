#include <SFML/Graphics.hpp>
#include "basic_tower.hpp"
#include "basic_projectile.hpp"
#include "strong_projectile.hpp"
#include "projectile.hpp"
#include "types.hpp"
#include <cmath>

namespace td{
  float hitbox_basic = 1.0f; //parameters radius and pointCount

  sf::Texture sprite_basic = sf::Texture();   //picture of the tower to here
        
  unsigned int attack_speed_basic = 10;  //can adjust these later

  float range_basic = 10.0f;   

  Basic_tower::Basic_tower(types::Position position, float rotation_angle):
  Tower(position, hitbox_basic, sprite_basic, rotation_angle, attack_speed_basic, range_basic) {}

  types::Position GetProjectStartPos(types::Position centre, float radius, float angle){
    types::Position result;
    result.x = centre.x + radius + cos(angle);  //angle should be in radians
    result.y = centre.y + radius + sin(angle);
    return result;
  }

  std::vector<projectiles::Projectile> Basic_tower::shoot(std::vector<projectiles::Projectile> vector) 
  {
    if(this->getLevel() == 1){
      projectiles::Basic_projectile newProjectile = projectiles::Basic_projectile
      (GetProjectStartPos(this->getPosition(),this->getHitbox(),this->getRotation())
      , this->getRotation(), 10);     ///Projectile starts from the edge of the tower
      vector.push_back(newProjectile);
      return vector;
    }
    else if(this->getLevel() == 2){
      projectiles::Basic_projectile newProjectile = projectiles::Basic_projectile
      (GetProjectStartPos(this->getPosition(),this->getHitbox(),this->getRotation()),
       this->getRotation(), 20); 
      vector.push_back(newProjectile);
      return vector;
    }
    else if(this->getLevel() == 3){
      projectiles::Basic_projectile newProjectile = projectiles::Basic_projectile
      (GetProjectStartPos(this->getPosition(),this->getHitbox(),this->getRotation()),
       this->getRotation(), 30); 
      vector.push_back(newProjectile);
      return vector;
    }
    else{
      projectiles::Strong_projectile newProjectile = projectiles::Strong_projectile
      (GetProjectStartPos(this->getPosition(),this->getHitbox(),this->getRotation()),
       this->getRotation()); 
      vector.push_back(newProjectile);
      return vector;
  }
  }

}