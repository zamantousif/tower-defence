#pragma once

#include <cmath>

#include "types.hpp"

namespace td {
/// Constant for PI (in radians)
constexpr double PI = 3.14;
///  \brief This file contains functions to check collision between different
/// shapes like collision between two circles, circle and a convex
/// polygon. Call these functions wherever there is a need to check for
/// collisions between the mentioned shapes.

/// \brief Function to calculate the distance between two points 1 and 2
/// \param p1 Position of point 1
/// \param p1 Position of point 2
/// \return Euclidean distance between point 1 and 2 using distance formula
float EuclideanDistance(td::types::Position p1, td::types::Position p2);

/// \brief Function to find the 2D angle between vectors (x1, y1) & (x2, y2)
/// \param x1 X coordinate of vector 1
/// \param y1 Y coordinate of vector 1
/// \param x2 X coordinate of vector 2
/// \param y2 Y coordinate of vector 2
/// \return Angle (in radians) made by vector 1 to vector 2. Angle is
/// positive anticlockwise and between -PI to +PI.
double Angle2D(double x1, double y1, double x2, double y2);

/// \brief Function to check if the circle center is inside a polygon or not
/// \param p Position of the center of circle
/// \param edges Vector of all edges that make up the polygon
/// \return True if the circle center is inside the polygon, false otherwise
bool IsCircleCenterInsidePolygon(
    td::types::Position p,
    std::vector<std::pair<td::types::Position, td::types::Position>> edges);

/// \brief Function to check if the circle intersects a polygon edge or not
/// \param p Position of the center of circle
/// \param r Radius of the circle
/// \param edge A given edge of the polygon
/// \return True if the circle intersects with the given edge, false otherwise
bool IsCircleIntersectingPolygonEdge(
    td::types::Position p, float r,
    std::pair<td::types::Position, td::types::Position> edge);

/// \brief Function to check if a circle is colliding with another circle or not
/// \param p1 Position of the center of circle 1
/// \param r1 Radius of the circle 1
/// \param p2 Position of the center of circle 2
/// \param r2 Radius of the circle 2
/// \return True if the two circles are colliding, false otherwise
bool IsCircleCollidingWithCircle(td::types::Position p1, float r1,
                                 td::types::Position p2, float r2);

/// \brief Function to check if a circle is colliding with a polygon or not
/// \param p Position of the center of circle
/// \param r Radius of the circle
/// \param polygon_points Vector of all corner points that make up the polygon
/// \return True if the circle is colliding with the polygon, false otherwise
bool IsCircleCollidingWithPolygon(
    td::types::Position p, float r,
    std::vector<td::types::Position> polygon_points);

}  // namespace td
