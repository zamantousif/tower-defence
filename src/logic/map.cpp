#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

namespace td {
Map::Map(const std::string& background_image_path,
         std::vector<td::types::Position> enemy_path,
         std::vector<td::types::BlockedRegion> blocked_regions)
    : background_image_path_(background_image_path),
      enemy_path_(enemy_path),
      blocked_regions_(blocked_regions) {}

const std::string& Map::getBackgroundImagePath() {
  return background_image_path_;
}

std::vector<td::types::Position>& Map::getEnemyPath() { return enemy_path_; }
const std::vector<td::types::Position>& Map::getEnemyPath() const {
  return enemy_path_;
}

std::vector<td::types::BlockedRegion>& Map::getBlockedRegions() {
  return blocked_regions_;
}

const std::vector<td::types::BlockedRegion>& Map::getBlockedRegions() const {
  return blocked_regions_;
}

Map* Map::LoadFromFile(const std::string& file_path) {
  std::ifstream json_file = std::ifstream(file_path);
  nlohmann::json json;
  json_file >> json;

  const std::string& path_to_image = json.at("backgroundImage");
  const std::vector<std::array<float, 2>> raw_enemy_path = json.at("enemyPath");
  const std::vector<std::vector<std::array<float, 2>>> raw_blocked_regions =
      json.at("blockedRegions");

  // Turn the raw path data into a vector that contains Positions
  std::vector<td::types::Position> enemy_path =
      std::vector<td::types::Position>();
  enemy_path.reserve(raw_enemy_path.size());
  for (auto it = raw_enemy_path.begin(); it != raw_enemy_path.end(); it++) {
    enemy_path.push_back(td::types::Position((*it)[0], (*it)[1]));
  }

  // Turn the raw region data into a vector that contains BlockedRegions
  std::vector<td::types::BlockedRegion> blocked_regions =
      std::vector<sf::ConvexShape>();
  blocked_regions.reserve(raw_blocked_regions.size());
  for (auto it = raw_blocked_regions.begin(); it != raw_blocked_regions.end();
       it++) {
    // Turn a vector of arrays into a vector of BlockedRegions
    td::types::BlockedRegion new_region = td::types::BlockedRegion();
    new_region.setPointCount(it->size());
    size_t i = 0;
    for (auto vertex_it = it->begin(); vertex_it != it->end(); vertex_it++) {
      new_region.setPoint(i, sf::Vector2f((*vertex_it)[0], (*vertex_it)[1]));
      i++;
    }
    blocked_regions.push_back(new_region);
  }

  return new Map(path_to_image, enemy_path, blocked_regions);
}

td::types::Position Map::GetStartingPosition() { return enemy_path_.front(); }

}  // namespace td