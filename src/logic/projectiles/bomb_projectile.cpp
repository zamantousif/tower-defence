#include "bomb_projectile.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

namespace td {
float hitbox_bomb = 1.0f;

sf::Texture* texture_bomb = nullptr;  // picture of the projectile to here

bool is_armor_piercing_bomb = true;

unsigned int enemy_pierced_count_bomb = 1;

Bomb_projectile::Bomb_projectile(sf::Vector2<float> position,
                                 float rotation_angle, int damage,
                                 sf::Texture* texture_projectile)
    : Projectile(position, hitbox_bomb, texture_projectile, rotation_angle, damage,
                 is_armor_piercing_bomb, enemy_pierced_count_bomb) {}

// travel function for updating the movement of the projectile
types::Position travel(types::Position start, float travel_distance,
                       float angle) {
  types::Position end_location;
  end_location.x =
      start.x + travel_distance + cos(angle);  // angle should be in radians
  end_location.y = start.y + travel_distance + sin(angle);
  return end_location;
}

//void Bomb_projectile::Update(td::types::Time dt) { (void)dt; }
}  // namespace td::projectiles