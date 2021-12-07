#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <vector>

#include "types.hpp"

namespace td {
class Map {
 public:
  Map(const std::string& background_image_path,
      std::vector<td::types::Position> enemy_path,
      std::vector<td::types::BlockedRegion> blocked_regions);

  const std::string& getBackgroundImagePath();

  std::vector<td::types::Position>& getEnemyPath();
  const std::vector<td::types::Position>& getEnemyPath() const;

  std::vector<td::types::BlockedRegion>& getBlockedRegions();
  const std::vector<td::types::BlockedRegion>& getBlockedRegions() const;

  static Map* LoadFromFile(const std::string& file_name);

 private:
  const std::string& background_image_path_;
  std::vector<td::types::Position> enemy_path_;
  std::vector<td::types::BlockedRegion> blocked_regions_;
};
}  // namespace td
