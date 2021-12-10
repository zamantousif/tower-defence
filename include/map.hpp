#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <vector>

#include "types.hpp"

namespace td {
class Map {
 public:
  /// \param background_image_path Path to the map background
  /// \param enemy_path Defines the path that the enemies take
  /// \param blocked_regions Defines regions that towers can't be placed on
  Map(const std::string& background_image_path,
      std::vector<td::types::Position> enemy_path,
      std::vector<td::types::BlockedRegion> blocked_regions);

  /// \return A path to the background image
  const std::string& getBackgroundImagePath();

  /// \return A reference to the enemy path
  std::vector<td::types::Position>& getEnemyPath();
  /// \return A const reference to the enemy path
  const std::vector<td::types::Position>& getEnemyPath() const;

  /// \return A reference to a vector of the blocked regions
  std::vector<td::types::BlockedRegion>& getBlockedRegions();
  /// \return A const reference to a vector of the blocked regions
  const std::vector<td::types::BlockedRegion>& getBlockedRegions() const;

  /// \param file_name Path to the JSON file to load the Map from
  /// 
  /// \return A pointer to a Map that was loaded from the given file
  static Map* LoadFromFile(const std::string& file_name);

 private:
  const std::string& background_image_path_;
  std::vector<td::types::Position> enemy_path_;
  std::vector<td::types::BlockedRegion> blocked_regions_;
};
}  // namespace td
