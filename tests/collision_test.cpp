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

TEST_F(CollisionTest, EuclideanDistance) {
  // Act
  td::types::Position p, A, B, C, D, O;
  p = sf::Vector2f(0.0f, 1.0f);
  A = sf::Vector2f(0.0f, 1.0f);
  B = sf::Vector2f(1.0f, 1.0f);
  C = sf::Vector2f(1.0f, 2.0f);
  D = sf::Vector2f(0.0f, 2.0f);
  O = sf::Vector2f(0.0f, 0.0f);

  // Arrange
  double dist_edgeAB = td::EuclideanDistance(A, B);
  double dist_edgeBC = td::EuclideanDistance(B, C);
  double dist_edgeCD = td::EuclideanDistance(C, D);
  double dist_edgeDA = td::EuclideanDistance(D, A);
  double dist_edgeOD = td::EuclideanDistance(O, D);
  double dist_edgeAC = td::EuclideanDistance(A, C);
  double dist_edgeDB = td::EuclideanDistance(D, B);

  // Assert
  EXPECT_FLOAT_EQ(dist_edgeAB, 1.0);
  EXPECT_FLOAT_EQ(dist_edgeBC, 1.0);
  EXPECT_FLOAT_EQ(dist_edgeCD, 1.0);
  EXPECT_FLOAT_EQ(dist_edgeDA, 1.0);
  EXPECT_FLOAT_EQ(dist_edgeOD, 2.0);
  EXPECT_FLOAT_EQ(dist_edgeAC, sqrt(2.0));
  EXPECT_FLOAT_EQ(dist_edgeDB, sqrt(2.0));
}

TEST_F(CollisionTest, IsPointBetween) {
  // Act
  td::types::Position p, A, B, C, D, O;
  p = sf::Vector2f(0.0f, 1.0f);
  A = sf::Vector2f(0.0f, 1.0f);
  B = sf::Vector2f(1.0f, 1.0f);
  C = sf::Vector2f(1.0f, 2.0f);
  D = sf::Vector2f(0.0f, 2.0f);
  O = sf::Vector2f(0.0f, 0.0f);

  // Arrange
  bool is_p_on_edgeAB = td::IsPointBetween(A, p, B);
  bool is_p_on_edgeBC = td::IsPointBetween(B, p, C);
  bool is_p_on_edgeCD = td::IsPointBetween(C, p, D);
  bool is_p_on_edgeDA = td::IsPointBetween(D, p, A);
  bool is_p_on_edgeOD = td::IsPointBetween(O, p, D);

  // Assert
  EXPECT_TRUE(is_p_on_edgeAB);
  EXPECT_FALSE(is_p_on_edgeBC);
  EXPECT_FALSE(is_p_on_edgeCD);
  EXPECT_TRUE(is_p_on_edgeDA);
  EXPECT_TRUE(is_p_on_edgeOD);
}

TEST_F(CollisionTest, Angle2D) {
  // Arrange
  sf::Vector2f v1 = sf::Vector2f(3.0, 4.0);
  sf::Vector2f v2 = sf::Vector2f(4.0, 3.0);
  sf::Vector2f v3 = sf::Vector2f(7.0, 1.0);
  sf::Vector2f v4 = sf::Vector2f(5.0, 5.0);
  sf::Vector2f v5 = sf::Vector2f(-5.0, -5.0);
  // Act
  double angle12 = Angle2D(v1.x, v1.y, v2.x, v2.y);
  double angle21 = Angle2D(v2.x, v2.y, v1.x, v1.y);
  double angle33 = Angle2D(v3.x, v3.y, v3.x, v3.y);
  double angle34 = Angle2D(v3.x, v3.y, v4.x, v4.y);
  double angle43 = Angle2D(v4.x, v4.y, v3.x, v3.y);
  double angle45 = Angle2D(v4.x, v4.y, v5.x, v5.y);
  double angle54 = Angle2D(v5.x, v5.y, v4.x, v4.y);
  // Assert
  EXPECT_FLOAT_EQ(angle12, -acos(0.96f));
  EXPECT_FLOAT_EQ(angle21, acos(0.96f));
  EXPECT_FLOAT_EQ(angle33, 0.0f);
  EXPECT_FLOAT_EQ(angle34, acos(0.8f));
  EXPECT_FLOAT_EQ(angle43, -acos(0.8f));
  EXPECT_NEAR(angle45, td::PI, 0.005);
  EXPECT_NEAR(angle54, -td::PI, 0.005);
}

TEST_F(CollisionTest, CircleAtOrigin_CollidesWithSquare) {
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
