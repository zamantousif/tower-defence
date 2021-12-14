#include "collision.hpp"

#include <iostream>
namespace td {

double EuclideanDistance(td::types::Position p1, td::types::Position p2) {
  double distance = sqrt(pow((p1.x - p2.x), 2.0) + pow((p1.y - p2.y), 2.0));
  return distance;
}

bool IsPointBetween(td::types::Position a, td::types::Position p,
                    td::types::Position b) {
  // if p lies on ab => dist(pa) + dist(pb) = dist(ab)
  double dist = EuclideanDistance(p, a) + EuclideanDistance(p, b) -
                EuclideanDistance(a, b);
  return (fabs(dist - 0.0) < std::numeric_limits<double>::epsilon());
}

double Angle2D(double x1, double y1, double x2, double y2) {
  double angle1 = atan2(y1, x1);
  double angle2 = atan2(y2, x2);
  double d_angle = angle2 - angle1;
  while (d_angle > PI) {
    d_angle -= 2.0 * PI;
  }
  while (d_angle < -PI) {
    d_angle += 2.0 * PI;
  }
  return d_angle;
}

double DotProduct2D(td::types::Position a, td::types::Position b,
                    td::types::Position c) {
  return (double)((b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y));
}

double CrossProduct2D(td::types::Position a, td::types::Position b,
                      td::types::Position c) {
  return (double)(((b.x - a.x) * (c.y - b.y)) - ((b.y - a.y) * (c.x - b.x)));
}

bool IsCircleCenterInsidePolygon(
    td::types::Position p,
    std::vector<std::pair<td::types::Position, td::types::Position>> edges) {
  td::types::Position p1, p2;
  double angle = 0.0;
  for (auto& edge : edges) {
    // If point p lies on the edge
    if (IsPointBetween(edge.first, p, edge.second)) {
      return true;
    }
    p1.x = edge.first.x - p.x;
    p1.y = edge.first.y - p.y;
    p2.x = edge.second.x - p.x;
    p2.y = edge.second.y - p.y;
    angle += Angle2D(p1.x, p1.y, p2.x, p2.y);
  }
  if (abs(angle) < PI)
    return false;
  else
    return true;
}

bool IsCircleIntersectingLineSegment(
    td::types::Position p, float r,
    std::pair<td::types::Position, td::types::Position> line_segment) {
  ///> DotProduct2D(AB, p) > 0 => p is closest to B
  if (DotProduct2D(line_segment.first, line_segment.second, p) > 0.0) {
    ///> Check if distance to B <= hitbox of circle(p, r)
    return std::islessequal(EuclideanDistance(p, line_segment.second),
                            (double)r);
  }
  ///> DotProduct2D(BA, p) > 0 => p is closest to A
  if (DotProduct2D(line_segment.second, line_segment.first, p) > 0.0) {
    ///> Check if distance to A <= hitbox of circle(p, r)
    return std::islessequal(EuclideanDistance(p, line_segment.first),
                            (double)r);
  }
  ///> p is nearest to a point ON segment AB, distance = (AB x Ap)/|AB|
  double dist = (CrossProduct2D(line_segment.first, line_segment.second, p) /
                 EuclideanDistance(line_segment.first, line_segment.second));
  return std::islessequal(fabs(dist), (double)r);
}

bool IsCircleCollidingWithCircle(td::types::Position p1, float r1,
                                 td::types::Position p2, float r2) {
  double d = EuclideanDistance(p1, p2);
  float result = (static_cast<float>(d) - r1 - r2);
  if (std::islessequal(result, 0.0f)) {
    return true;
  }
  // result is > 0.0f or otherwise
  return false;
}

bool IsCircleCollidingWithPolygon(
    td::types::Position p, float r,
    std::vector<td::types::Position> polygon_points) {
  bool is_circle_center_inside_polygon = false;
  std::vector<std::pair<td::types::Position, td::types::Position>> edges;

  if (!polygon_points.empty()) {
    edges.clear();
    for (auto it = polygon_points.begin(); it != polygon_points.end(); ++it) {
      if (it == polygon_points.end() - 1) {
        // Add the last edge (last corner point to first corner point)
        edges.emplace_back(
            std::make_pair(polygon_points.back(), polygon_points.front()));
        break;
      }
      edges.emplace_back(std::make_pair(*it, *(it + 1)));
    }
  }

  for (auto& edge : edges) {
    if (IsCircleIntersectingLineSegment(p, r, edge)) return true;
  }
  is_circle_center_inside_polygon = IsCircleCenterInsidePolygon(p, edges);
  return is_circle_center_inside_polygon;
}

}  // namespace td
