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
  // ab.bc = (b1-a1)*(c1-b1) + (b2-a2)*(c2-b2)
  return (double)((b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y));
}

double CrossProduct2D(td::types::Position a, td::types::Position b,
                      td::types::Position c) {
  // ab x bc = (b1-a1)*(c2-b2) - (b2-a2)*(c1-b1)
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
  // If center p lies on the line segment
  if (IsPointBetween(line_segment.first, p, line_segment.second)) {
    return true;
  }
  // DotProduct2D(p, AB) > 0 => p is closest to A
  if (DotProduct2D(p, line_segment.first, line_segment.second) > 0.0) {
    // Check if distance to A <= hitbox of circle(p, r)
    return std::islessequal(EuclideanDistance(p, line_segment.first),
                            (double)r);
  }
  // DotProduct2D(AB, p) > 0 => p is closest to B
  if (DotProduct2D(line_segment.first, line_segment.second, p) > 0.0) {
    // Check if distance to B <= hitbox of circle(p, r)
    return std::islessequal(EuclideanDistance(p, line_segment.second),
                            (double)r);
  }
  // p is nearest to a point ON segment AB, distance = (p x AB)/|AB|
  double dist = (CrossProduct2D(line_segment.first, line_segment.second, p) /
                 EuclideanDistance(line_segment.first, line_segment.second));
  return std::islessequal(dist, (double)r);
}

bool IsCircleIntersectingPolygonEdge(
    td::types::Position p, float r,
    std::pair<td::types::Position, td::types::Position> edge) {
  double a = 0.0, b = 0.0, c = 0.0, D = 0.0;
  double x1, x2, y1, y2, xR, yR, root1, root2, x_root1, x_root2, y_root1,
      y_root2;
  bool is_root_on_polygon_edge = false;
  // If center p lies on the edge
  if (IsPointBetween(edge.first, p, edge.second)) {
    return true;
  }
  x1 = edge.first.x;
  y1 = edge.first.y;
  x2 = edge.second.x;
  y2 = edge.second.y;
  xR = p.x;
  yR = p.y;
  a = pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0);
  b = (2.0 * x1 * x2) - (2.0 * pow(x2, 2)) - (2.0 * x1 * xR) + (2.0 * x2 * xR) +
      (2.0 * y1 * y2) - (2.0 * pow(y2, 2.0)) - (2.0 * y1 * yR) +
      (2.0 * y2 * yR);
  c = pow(x2 - xR, 2.0) + pow(y2 - yR, 2.0) - pow(r, 2.0);
  D = pow(b, 2.0) - (4.0 * a * c);
  // find roots of the quadratic equation, given above coefficients &
  // discriminant
  if (std::isgreaterequal(D, 0.0)) {
    // float-point equality check with epsilon
    if (std::fabs(D - 0.0) < std::numeric_limits<double>::epsilon()) {
      // D == 0.0 => roots are equal
      root1 = -b / (2 * a);
      root2 = root1;
    } else {
      // D > 0.0 => roots are real but unequal
      root1 = (-b + sqrt(D)) / (2.0 * a);
      root2 = (-b - sqrt(D)) / (2.0 * a);
    }
    x_root1 = root1 * x1 + (1.0 - root1) * x2;
    x_root2 = root2 * x1 + (1.0 - root2) * x2;
    y_root1 = root1 * y1 + (1.0 - root1) * y2;
    y_root2 = root2 * y1 + (1.0 - root2) * y2;
    is_root_on_polygon_edge =
        IsPointBetween(edge.first,
                       td::types::Position(static_cast<float>(x_root1),
                                           static_cast<float>(y_root1)),
                       edge.second) ||
        IsPointBetween(edge.first,
                       td::types::Position(static_cast<float>(x_root2),
                                           static_cast<float>(y_root2)),
                       edge.second);
    return is_root_on_polygon_edge;
  }
  // D < 0 => Circle is not intersecting given edge of the Polygon
  return false;
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
      edges.emplace_back(std::make_pair(*it, *(it + 1)));
    }
    // Add the last edge (last corner point to first corner point)
    edges.emplace_back(
        std::make_pair(*polygon_points.end(), *polygon_points.begin()));
  }

  for (auto& edge : edges) {
    if (IsCircleIntersectingLineSegment(p, r, edge)) return true;
  }
  is_circle_center_inside_polygon = IsCircleCenterInsidePolygon(p, edges);
  return is_circle_center_inside_polygon;
}

}  // namespace td
