#include "collision.hpp"

#include "gtest/gtest.h"

namespace td {
namespace test {

// The fixture for testing class Object.
class CollisionTest : public ::testing::Test {
 protected:
  // Class members declared here can be used by all tests in the test suite
  // for CollisionTest.
};

TEST_F(CollisionTest, UnitCircleAtOrigin_CollidesWithRectangle) {
  // Arrange
  // Circle (p, r)
  td::types::Position p = sf::Vector2f(0.0f, 0.0f);
  float r = 1;
  // Rectangle ABCD
  td::types::Position A = sf::Vector2f(0.0f, 1.0f);
  td::types::Position B = sf::Vector2f(1.0f, 1.0f);
  td::types::Position C = sf::Vector2f(1.0f, 2.0f);
  td::types::Position D = sf::Vector2f(0.0f, 2.0f);
  std::vector<td::types::Position> polygon;
  polygon.emplace_back(A);
  polygon.emplace_back(B);
  polygon.emplace_back(C);
  polygon.emplace_back(D);
  std::vector<std::pair<td::types::Position, td::types::Position>> edges;
  std::pair<td::types::Position, td::types::Position> edge_AB, edge_BC, edge_CD,
      edge_DA;
  edge_AB = std::make_pair(A, B);
  edge_BC = std::make_pair(B, C);
  edge_CD = std::make_pair(C, D);
  edge_DA = std::make_pair(D, A);
  edges.emplace_back(edge_AB);
  edges.emplace_back(edge_BC);
  edges.emplace_back(edge_CD);
  edges.emplace_back(edge_DA);

  // Act
  bool is_circle_intersecting_AB =
      td::IsCircleIntersectingPolygonEdge(p, r, edge_AB);
  bool is_circle_intersecting_BC =
      td::IsCircleIntersectingPolygonEdge(p, r, edge_BC);
  bool is_circle_intersecting_CD =
      td::IsCircleIntersectingPolygonEdge(p, r, edge_CD);
  bool is_circle_intersecting_DA =
      td::IsCircleIntersectingPolygonEdge(p, r, edge_DA);
  bool is_circle_inside_polygon = td::IsCircleCenterInsidePolygon(p, edges);
  bool is_circle_colliding_with_polygon =
      td::IsCircleCollidingWithPolygon(p, r, polygon);

  // Assert
  EXPECT_TRUE(is_circle_intersecting_AB);
  EXPECT_FALSE(is_circle_intersecting_BC);
  EXPECT_FALSE(is_circle_intersecting_CD);
  EXPECT_TRUE(is_circle_intersecting_DA);
  EXPECT_FALSE(is_circle_inside_polygon);
  EXPECT_TRUE(is_circle_colliding_with_polygon);
}

}  // namespace test
}  // namespace td
