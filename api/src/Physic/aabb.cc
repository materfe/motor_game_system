//
// Created by Mat on 24.10.2024.
//

#include "Physic/aabb.h"
bool AABB::OverlapOnAxis(const core::Vec2<float> &axis, const std::vector<core::Vec2<float>> &vertices) const {
  // Project AABB onto the axis
  std::array<core::Vec2<float>, 4> aabbCorners = {
      core::Vec2<float>(min_x_bound_, min_y_bound_),
      core::Vec2<float>(max_x_bound_, min_y_bound_),
      core::Vec2<float>(min_x_bound_, max_y_bound_),
      core::Vec2<float>(max_x_bound_, max_y_bound_)
  };

  float aabbMin = ProjectPoint(aabbCorners[0], axis);
  float aabbMax = aabbMin;

  for (int i = 1; i < 4; ++i) {
    const auto projection = ProjectPoint(aabbCorners[i], axis);
    aabbMin = std::min(aabbMin, projection);
    aabbMax = std::max(aabbMax, projection);
  }

  // Project Polygon onto the axis
  float polyMin = ProjectPoint(vertices[0], axis);
  float polyMax = polyMin;

  for (std::size_t i = 1; i < vertices.size(); ++i) {
    const auto projection = ProjectPoint(vertices[i], axis);
    polyMin = std::min(polyMin, projection);
    polyMax = std::max(polyMax, projection);
  }

  // Check if projections overlap
  return !(aabbMax < polyMin || polyMax < aabbMin);
}

bool AABB::IsColliding(const AABB &other) const {
  // Check for separation on the x-axis
  if (max_x_bound_ < other.min_x_bound_ || other.max_x_bound_ < min_x_bound_) {
    return false;
  }
  // Check for separation on the y-axis
  if (max_y_bound_ < other.min_y_bound_ || other.max_y_bound_ < min_y_bound_) {
    return false;
  }
  // No separation found, the boxes must be colliding
  return true;
}

bool AABB::IsCollidingWithPolygon(Polygon &polygon) const {
  const auto &vertices = polygon.getVertices();

  // Axes to check for SAT: AABB axes (x, y) and Polygon edges' normals
  std::vector<core::Vec2<float>> axes = {
      {1.0f, 0.0f}, // x-axis
      {0.0f, 1.0f}  // y-axis
  };

  // Add the normals of the polygon edges as separating axes
  for (std::size_t i = 0; i < vertices.size(); ++i) {
    std::size_t next = (i + 1) % vertices.size();
    const float edge_x = vertices[next].x_ - vertices[i].x_;
    const float edge_y = vertices[next].y_ - vertices[i].y_;

    // Normal of the edge is (-edge_y, edge_x)
    axes.emplace_back(-edge_y, edge_x);
  }

  // Check for overlap on all axes
  for (const auto &axis : axes) {
    if (!OverlapOnAxis(axis, vertices)) {
      return false; // Separating axis found, no collision
    }
  }


  // No separating axis found, AABB and Polygon are colliding
  return true;
}


