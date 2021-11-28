#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <vector>

#include "types.hpp"

namespace td {
  class Map {
   public:
    Map(sf::Texture background_image, std::vector<td::types::Position> enemy_path, std::vector<td::types::BlockedRegion> blocked_regions);
    
    sf::Texture& getBackgroundImage();
    const sf::Texture& getBackgroundImage() const;
    
    std::vector<td::types::Position>& getEnemyPath();
    const std::vector<td::types::Position>& getEnemyPath() const;
    
    std::vector<td::types::BlockedRegion>& getBlockedRegions();
    const std::vector<td::types::BlockedRegion>& getBlockedRegions() const;
    
    static Map* LoadFromFile(const std::string& file_name);

   private:
    sf::Texture background_image_;
    std::vector<td::types::Position> enemy_path_;
    std::vector<td::types::BlockedRegion> blocked_regions_;
  };
}
