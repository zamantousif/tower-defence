/// \file collision.hpp
/// \brief This file contains functions to check collision between different
/// shapes like collision between two circles, circle and a convex
/// polygon. Call these functions wherever there is a need to check for
/// collisions between the mentioned shapes.

#pragma once
#include <cmath>

#include "types.hpp"

namespace td {
/// Constant for PI (in radians)
constexpr double PI = 3.14;

/// \brief Function to calculate the distance between two points 1 and 2
/// \param p1 Position of point 1
/// \param p1 Position of point 2
/// \return Euclidean distance between point 1 and 2 using distance formula
double EuclideanDistance(td::types::Position p1, td::types::Position p2);

/// \brief Check if a given point p is between two points a and b
/// \param a Position of point a (end-point of segment ab)
/// \param p Position of the test point p
/// \param b Position of point b (end-point of segment ab)
/// \return True if point p lies on the segment formed by a & b, false otherwise
bool IsPointBetween(td::types::Position a, td::types::Position p,
                    td::types::Position b);

/// \brief Function to find the 2D angle between vectors (x1, y1) & (x2, y2)
/// \param x1 X coordinate of vector 1
/// \param y1 Y coordinate of vector 1
/// \param x2 X coordinate of vector 2
/// \param y2 Y coordinate of vector 2
/// \return Angle (in radians) made by vector 1 to vector 2. Angle is
/// positive anticlockwise and between -PI to +PI.
double Angle2D(double x1, double y1, double x2, double y2);

/// \brief Find the 2D dot product of 2 line segments made by points a, b & c
/// \param a Position of point a
/// \param b Position of point b
/// \param c Position of point c
/// \return 2D dot product of line segments ab to bc as given by the formula
/// ab.bc = (b1-a1)*(c1-b1) + (b2-a2)*(c2-b2)
double DotProduct2D(td::types::Position a, td::types::Position b,
                    td::types::Position c);

/// \brief Find the 2D cross product of 2 line segments made by points a, b & c
/// \param a Position of point a
/// \param b Position of point b
/// \param c Position of point c
/// \return 2D cross product of line segments ab and bc as given by the formula
/// ab x bc = (b1-a1)*(c2-b2) - (b2-a2)*(c1-b1)
double CrossProduct2D(td::types::Position a, td::types::Position b,
                      td::types::Position c);

/// \brief Check if a given circle intersects a given line segment or not
/// \param p Position of the center of circle
/// \param r Radius of the circle
/// \param line_segment Line segment containing two end points
/// \return True if the circle intersects the line segment, false otherwise
/// \details Given a line segment and a circle, there are 3 cases:
/// 1. The circle center is closer to one end point of line segment
/// 2. The circle center is closer to the other end point of line segment
/// 3. The circle center is closer to another point that lies on line segment
/// The cases 1, 2 occur when the dot product of the respective line segment
/// (starting with the respective end point) to the circle center is > 0. Case 3
/// occurs otherwise. In each case, the closest distance is computed and checked
/// if it is less than or equal to the circle radius.
bool IsCircleIntersectingLineSegment(
    td::types::Position p, float r,
    std::pair<td::types::Position, td::types::Position> line_segment);

/// \brief Function to check if the circle center is inside a polygon or not
/// \param p Position of the center of circle
/// \param edges Vector of all edges that make up the polygon
/// \return True if the circle center is inside the polygon, false otherwise
bool IsCircleCenterInsidePolygon(
    td::types::Position p,
    std::vector<std::pair<td::types::Position, td::types::Position>> edges);

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
