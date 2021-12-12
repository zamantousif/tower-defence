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
  sf::Vector2f v6 = sf::Vector2f(0.0, 0.0);
  sf::Vector2f v7 = sf::Vector2f(3.0, 0.0);
  // Act
  double angle12 = Angle2D(v1.x, v1.y, v2.x, v2.y);
  double angle21 = Angle2D(v2.x, v2.y, v1.x, v1.y);
  double angle33 = Angle2D(v3.x, v3.y, v3.x, v3.y);
  double angle34 = Angle2D(v3.x, v3.y, v4.x, v4.y);
  double angle43 = Angle2D(v4.x, v4.y, v3.x, v3.y);
  double angle45 = Angle2D(v4.x, v4.y, v5.x, v5.y);
  double angle54 = Angle2D(v5.x, v5.y, v4.x, v4.y);
  double angle66 = Angle2D(v6.x, v6.y, v6.x, v6.y);
  double angle67 = Angle2D(v6.x, v6.y, v7.x, v7.y);
  // Assert
  EXPECT_FLOAT_EQ(angle12, -acos(0.96f));
  EXPECT_FLOAT_EQ(angle21, acos(0.96f));
  EXPECT_FLOAT_EQ(angle33, 0.0f);
  EXPECT_FLOAT_EQ(angle34, acos(0.8f));
  EXPECT_FLOAT_EQ(angle43, -acos(0.8f));
  EXPECT_NEAR(angle45, td::PI, 0.005);
  EXPECT_NEAR(angle54, -td::PI, 0.005);
  EXPECT_FLOAT_EQ(angle66, 0.0f);
  EXPECT_FLOAT_EQ(angle67, 0.0f);
}

TEST_F(CollisionTest, IsCircleCenterInsidePolygon) {
  // Arrange
  // Circle (p, r)
  td::types::Position p1 = sf::Vector2f(0.0f, 0.0f);
  td::types::Position p2 = sf::Vector2f(3.0f, 0.0f);
  td::types::Position p3 = sf::Vector2f(3.0f, 3.0f);
  td::types::Position p4 = sf::Vector2f(5.0f, -5.0f);
  td::types::Position p5 = sf::Vector2f(8.0f, 8.01f);
  // Polygon ABCDE
  td::types::Position A = sf::Vector2f(0.0f, 0.0f);
  td::types::Position B = sf::Vector2f(5.0f, 0.0f);
  td::types::Position C = sf::Vector2f(8.0f, 8.0f);
  td::types::Position D = sf::Vector2f(3.0f, 12.0f);
  td::types::Position E = sf::Vector2f(-2.0f, 7.0f);
  std::vector<std::pair<td::types::Position, td::types::Position>> edges;
  std::pair<td::types::Position, td::types::Position> edge_AB, edge_BC, edge_CD,
      edge_DE, edge_EA;
  edge_AB = std::make_pair(A, B);
  edge_BC = std::make_pair(B, C);
  edge_CD = std::make_pair(C, D);
  edge_DE = std::make_pair(D, E);
  edge_EA = std::make_pair(E, A);
  edges.emplace_back(edge_AB);
  edges.emplace_back(edge_BC);
  edges.emplace_back(edge_CD);
  edges.emplace_back(edge_DE);
  edges.emplace_back(edge_EA);
  // Act
  bool is_circle1_inside = IsCircleCenterInsidePolygon(p1, edges);
  bool is_circle2_inside = IsCircleCenterInsidePolygon(p2, edges);
  bool is_circle3_inside = IsCircleCenterInsidePolygon(p3, edges);
  bool is_circle4_inside = IsCircleCenterInsidePolygon(p4, edges);
  bool is_circle5_inside = IsCircleCenterInsidePolygon(p5, edges);
  // Assert
  EXPECT_TRUE(is_circle1_inside);
  EXPECT_TRUE(is_circle2_inside);
  EXPECT_TRUE(is_circle3_inside);
  EXPECT_FALSE(is_circle4_inside);
  EXPECT_FALSE(is_circle5_inside);
}

TEST_F(CollisionTest, IsCircleIntersectingPolygonEdge) {
  // Arrange
  // Circle (p, r)
  td::types::Position p1 = sf::Vector2f(0.0f, 0.0f);
  float r = 1;
  // Polygon ABCDE
  td::types::Position A = sf::Vector2f(0.0f, 0.0f);
  td::types::Position B = sf::Vector2f(5.0f, 0.0f);
  td::types::Position C = sf::Vector2f(8.0f, 8.0f);
  td::types::Position D = sf::Vector2f(3.0f, 12.0f);
  td::types::Position E = sf::Vector2f(-2.0f, 7.0f);
  std::pair<td::types::Position, td::types::Position> edge_AB, edge_BC, edge_CD,
      edge_DE, edge_EA, edge_AE;
  edge_AB = std::make_pair(A, B);
  edge_BC = std::make_pair(B, C);
  edge_CD = std::make_pair(C, D);
  edge_DE = std::make_pair(D, E);
  edge_EA = std::make_pair(E, A);
  // Act
  bool is_circle_intersecting_AB =
      td::IsCircleIntersectingPolygonEdge(p1, r, edge_AB);
  bool is_circle_intersecting_BC =
      td::IsCircleIntersectingPolygonEdge(p1, r, edge_BC);
  bool is_circle_intersecting_CD =
      td::IsCircleIntersectingPolygonEdge(p1, r, edge_CD);
  bool is_circle_intersecting_DE =
      td::IsCircleIntersectingPolygonEdge(p1, r, edge_DE);
  bool is_circle_intersecting_EA =
      td::IsCircleIntersectingPolygonEdge(p1, r, edge_EA);
  // Arrange
  EXPECT_TRUE(is_circle_intersecting_AB);
  EXPECT_FALSE(is_circle_intersecting_BC);
  EXPECT_FALSE(is_circle_intersecting_CD);
  EXPECT_FALSE(is_circle_intersecting_DE);
  EXPECT_TRUE(is_circle_intersecting_EA);
  EXPECT_TRUE(td::IsCircleIntersectingPolygonEdge(p1, 5.0f, edge_AB));
  EXPECT_TRUE(td::IsCircleIntersectingPolygonEdge(p1, 5.0f, edge_BC));
  EXPECT_FALSE(td::IsCircleIntersectingPolygonEdge(p1, 5.0f, edge_CD));
  EXPECT_FALSE(td::IsCircleIntersectingPolygonEdge(p1, 5.0f, edge_DE));
  EXPECT_TRUE(td::IsCircleIntersectingPolygonEdge(p1, 5.0f, edge_EA));
}

TEST_F(CollisionTest, IsCircleCollidingWithCircle) {
  // Arrange
  // Circle (p, r)
  td::types::Position p1 = sf::Vector2f(0.0f, 0.0f);
  float r1 = 1;
  td::types::Position p2 = sf::Vector2f(1.0f, 1.0f);
  float r2 = 1;
  td::types::Position p3 = sf::Vector2f(2.0f, 1.5f);
  float r3 = 1;
  // Act
  bool are_c1_c1_colliding = IsCircleCollidingWithCircle(p1, r1, p1, r1);
  bool are_c1_c2_colliding = IsCircleCollidingWithCircle(p1, r1, p2, r2);
  bool are_c1_c3_colliding = IsCircleCollidingWithCircle(p1, r1, p3, r3);
  bool are_c2_c3_colliding = IsCircleCollidingWithCircle(p2, r2, p3, r3);
  // Assert
  EXPECT_TRUE(are_c1_c1_colliding);
  EXPECT_TRUE(are_c1_c2_colliding);
  EXPECT_FALSE(are_c1_c3_colliding);
  EXPECT_TRUE(are_c2_c3_colliding);
  EXPECT_TRUE(IsCircleCollidingWithCircle(p1, 2.0f, p2, r2));
  EXPECT_TRUE(IsCircleCollidingWithCircle(p1, 2.0f, p3, r3));
  EXPECT_TRUE(IsCircleCollidingWithCircle(p1, 2.0f, p1, 0.01f));
}

TEST_F(CollisionTest, IsCircleCollidingWithPolygon) {
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
