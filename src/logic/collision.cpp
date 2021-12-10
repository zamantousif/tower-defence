#include "collision.hpp"

namespace td {

float EuclideanDistance(td::types::Position p1, td::types::Position p2) {
  float distance = pow((p1.x - p2.x), 2) + pow((p1.y - p2.x), 2);
  return distance;
}

double Angle2D(double x1, double y1, double x2, double y2) {
  double angle1 = atan2(y1, x1);
  double angle2 = atan2(y2, x2);
  double d_angle = angle2 - angle1;
  while (d_angle > PI) {
    d_angle -= 2 * PI;
  }
  while (d_angle < -PI) {
    d_angle += 2 * PI;
  }
  return d_angle;
}

bool IsCircleCenterInsidePolygon(
    td::types::Position p,
    std::vector<std::pair<td::types::Position, td::types::Position>> edges) {
  td::types::Position p1, p2;
  double angle = 0;
  for (auto& edge : edges) {
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

bool IsCircleIntersectingPolygonEdge(
    td::types::Position p, float r,
    std::pair<td::types::Position, td::types::Position> edge) {
  double a = 0, b = 0, c = 0, D = 0;
  double x1, x2, y1, y2, xR, yR;
  x1 = edge.first.x;
  y1 = edge.first.y;
  x2 = edge.second.x;
  y2 = edge.second.y;
  xR = p.x;
  yR = p.y;
  a = pow(x1 - x2, 2) + pow(y1 - y2, 2);
  b = 2 * x1 * x2 - 2 * pow(x2, 2) - 2 * x1 * xR + 2 * x2 * xR + 2 * y1 * y2 -
      2 * pow(y2, 2) - 2 * y1 * yR + 2 * y2 * yR;
  c = pow(x2 - xR, 2) + pow(y2 - yR, 2) - pow(r, 2);
  D = pow(b, 2) - (4 * a * c);
  if (D >= 0) {
    return true;
  }
  // D < 0 => Circle is not intersecting given edge of the Polygon
  return false;
}

bool IsCircleCollidingWithCircle(td::types::Position p1, float r1,
                                 td::types::Position p2, float r2) {
  float d = EuclideanDistance(p1, p2);
  float result = abs(d - r1 - r2);
  if (result <= 0.0f) {
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
    for (auto it = polygon_points.begin(); it != polygon_points.end(); ++it) {
      edges.emplace_back(std::make_pair(*it, *(it + 1)));
    }
    // Add the last edge (last corner point to first corner point)
    edges.emplace_back(
        std::make_pair(*polygon_points.end(), *polygon_points.begin()));
  }

  for (auto& edge : edges) {
    if (IsCircleIntersectingPolygonEdge(p, r, edge))
      return true;
  }
  is_circle_center_inside_polygon = IsCircleCenterInsidePolygon(p, edges);
  return is_circle_center_inside_polygon;
}

}  // namespace td
