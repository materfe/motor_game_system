//
// Created by Mat on 23.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_MATH_FOR_CIRCLES_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_MATH_FOR_CIRCLES_H_

#include "physical_circle.h"
#include "physical_polygon.h"
#include "aabb.h"
#include <array>

namespace Physic {

//what we use for collision calculus
[[nodiscard]] constexpr float ProjectPoint(const core::Vec2<float> &point, const core::Vec2<float> &axis) {
  return point.x_ * axis.x_ + point.y_ * axis.y_;
}
// Project all points of a polygon onto a given axis
[[nodiscard]] static const core::Vec2<float> ProjectPolygonOntoAxis(const PhysicalPolygon &polygon,
                                                                    const core::Vec2<float> &axis) {
  const auto &vertices = polygon.GetVertices();
  float min = ProjectPoint(vertices[0], axis);
  float max = min;

  // Project each vertex onto the axis and keep track of min and max projections
  for (std::size_t i = 1; i < vertices.size(); ++i) {
    float projection = ProjectPoint(vertices[i], axis);
    min = std::min(min, projection);
    max = std::max(max, projection);
  }
  return {min, max}; // returns the projection range
}
// Check if two projections on an axis overlap
[[nodiscard]] static const bool DoProjectionsOverlap(const core::Vec2<float> &proj1, const core::Vec2<float> &proj2) {
  return !(proj1.y_ < proj2.x_ || proj2.y_ < proj1.x_); // true if projections overlap
}
[[nodiscard]] static const bool OverlapOnAxis(const AABB &aabb, const core::Vec2<float> &axis,
                                              const std::vector<core::Vec2<float>> &vertices) {
  std::array<core::Vec2<float>, 4> aabbCorners = {
      core::Vec2<float>(aabb.GetMinX(), aabb.GetMinY()),
      core::Vec2<float>(aabb.GetMaxX(), aabb.GetMinY()),
      core::Vec2<float>(aabb.GetMinX(), aabb.GetMaxY()),
      core::Vec2<float>(aabb.GetMaxX(), aabb.GetMaxY())
  };
  float aabbMin = Physic::ProjectPoint(aabbCorners[0], axis);
  float aabbMax = aabbMin;

  for (int i = 1; i < 4; ++i) {
    const auto projection = Physic::ProjectPoint(aabbCorners[i], axis);
    aabbMin = std::min(aabbMin, projection);
    aabbMax = std::max(aabbMax, projection);
  }

  float polyMin = Physic::ProjectPoint(vertices[0], axis);
  float polyMax = polyMin;

  for (std::size_t i = 1; i < vertices.size(); ++i) {
    const auto projection = Physic::ProjectPoint(vertices[i], axis);
    polyMin = std::min(polyMin, projection);
    polyMax = std::max(polyMax, projection);
  }
  return !(aabbMax < polyMin || polyMax < aabbMin);
}

// collision circle - circle
[[nodiscard]] static const bool AreTwoCirclesColliding(const PhysicalCircle &circle_1, const PhysicalCircle &circle_2) {
  // Calculate the squared distance between the two centers
  const float deltaX = circle_2.GetPosition().x_ - circle_1.GetPosition().x_;
  const float deltaY = circle_2.GetPosition().y_ - circle_1.GetPosition().y_;
  const float distanceSquared = deltaX * deltaX + deltaY * deltaY;

  // Calculate the sum of the radi (collision happens if the distance between centers <= sum of radi)
  const float radiSum = circle_1.GetRadius() + circle_2.GetRadius();
  return distanceSquared <= radiSum * radiSum;
}
// collision polygon - polygon
[[nodiscard]] static const bool AreTwoPolygonsColliding(const PhysicalPolygon &polygon1,
                                                        const PhysicalPolygon &polygon2) {
  const auto &vertices1 = polygon1.GetVertices();
  const auto &vertices2 = polygon2.GetVertices();

  // Generate separating axes from polygon1 and polygon2 edges
  std::vector<core::Vec2<float>> axes;

  // Add axes from polygon1 edges
  for (std::size_t i = 0; i < vertices1.size(); ++i) {
    std::size_t next = (i + 1) % vertices1.size();
    float edge_x = vertices1[next].x_ - vertices1[i].x_;
    float edge_y = vertices1[next].y_ - vertices1[i].y_;
    axes.emplace_back(-edge_y, edge_x); // perpendicular (normal) to edge
  }

  // Add axes from polygon2 edges
  for (std::size_t i = 0; i < vertices2.size(); ++i) {
    std::size_t next = (i + 1) % vertices2.size();
    float edge_x = vertices2[next].x_ - vertices2[i].x_;
    float edge_y = vertices2[next].y_ - vertices2[i].y_;
    axes.emplace_back(-edge_y, edge_x); // perpendicular (normal) to edge
  }

  // Check for overlap on all axes
  for (const auto &axis : axes) {
    auto proj1 = Physic::ProjectPolygonOntoAxis(polygon1, axis);
    auto proj2 = Physic::ProjectPolygonOntoAxis(polygon2, axis);

    if (!DoProjectionsOverlap(proj1, proj2)) {
      return false; // A separating axis was found, so the polygons are not colliding
    }
  }

  // No separating axis was found, so the polygons are colliding
  return true;
}
// collision aabb - aabb
[[nodiscard]] static const bool AreTwoAabbsColliding(const AABB &aabb1, const AABB &aabb2) {
  //check overlap from top-right corner
  if (aabb1.GetMaxX() >= aabb2.GetMinX() && aabb1.GetMinX() <= aabb2.GetMinX() && aabb1.GetMaxY() >= aabb2.GetMinY()
      && aabb1.GetMinY() <= aabb2.GetMinY()) {
    return true;
  }

  //check overlap from bottom-right corner
  if (aabb1.GetMaxX() >= aabb2.GetMinX() && aabb1.GetMinX() <= aabb2.GetMinX() && aabb1.GetMinY() <= aabb2.GetMaxY()
      && aabb1.GetMaxY() >= aabb2.GetMaxY()) {
    return true;
  }

  //check overlap from bottom-left corner
  if (aabb1.GetMinX() <= aabb2.GetMaxX() && aabb1.GetMaxX() >= aabb2.GetMaxX() && aabb1.GetMinY() <= aabb2.GetMaxY()
      && aabb1.GetMaxY() >= aabb2.GetMaxY()) {
    return true;
  }

  //check overlap from top-left corner
  if (aabb1.GetMinX() <= aabb2.GetMaxX() && aabb1.GetMaxX() >= aabb2.GetMaxX() && aabb1.GetMaxY() >= aabb2.GetMinY()
      && aabb1.GetMinY() <= aabb2.GetMinY()) {
    return true;
  }
  return false;
}

// collision aabb - polygon and polygon - aabb
[[nodiscard]] static const bool IsOneAabbCollidingWithOnePolygon(const AABB &aabb, const PhysicalPolygon &polygon) {
  const auto &vertices = polygon.GetVertices();

  // Axes to check for SAT: AABB axes (x, y) and DrawablePolygon edges' normals
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
    if (!Physic::OverlapOnAxis(aabb, axis, vertices)) {
      return false; // Separating axis found, no collision
    }
  }

  // No separating axis found, AABB and DrawablePolygon are colliding
  return true;
}
[[nodiscard]] static const bool IsOnePolygonCollidingWithOneAabb(const PhysicalPolygon &polygon, const AABB &aabb) {
  return IsOneAabbCollidingWithOnePolygon(aabb, polygon);
}
// collision circle - aabb and aabb - circle
[[nodiscard]] static const bool IsOneCircleCollidingWithOneAabb(const PhysicalCircle &circle, const AABB &aabb) {
  const auto circlePos = circle.GetPosition();

  float closestX = std::max(aabb.GetMinX(), std::min(circlePos.x_, aabb.GetMaxX()));
  float closestY = std::max(aabb.GetMinY(), std::min(circlePos.y_, aabb.GetMaxY()));

  float deltaX = circlePos.x_ - closestX;
  float deltaY = circlePos.y_ - closestY;

  return (deltaX * deltaX + deltaY * deltaY) <= (circle.GetRadius() * circle.GetRadius());
}
[[nodiscard]] static const bool IsOneAabbCollidingWithOneCircle(const AABB &aabb, const PhysicalCircle &circle) {

  return IsOneCircleCollidingWithOneAabb(circle, aabb);
}
// collision circle - polygon and polygon - circle
[[nodiscard]] static const bool IsOneCircleCollidingWithOnePolygon(const PhysicalCircle &circle,
                                                                   const PhysicalPolygon &polygon) {
  const auto circlePos = circle.GetPosition();
  const auto &vertices = polygon.GetVertices();

  float closestDistSq = std::numeric_limits<float>::max();

  //does a lot of calculus to test each vertex and its distance to the edge of the circle
  for (std::size_t i = 0; i < vertices.size(); ++i) {
    std::size_t next = (i + 1) % vertices.size();
    core::Vec2<float> edge = {vertices[next].x_ - vertices[i].x_, vertices[next].y_ - vertices[i].y_};
    core::Vec2<float> toCircle = {circlePos.x_ - vertices[i].x_, circlePos.y_ - vertices[i].y_};
    float t = std::max(0.0f, std::min(1.0f, (toCircle.x_ * edge.x_ + toCircle.y_ * edge.y_) /
        (edge.x_ * edge.x_ + edge.y_ * edge.y_)));
    core::Vec2<float> closestPoint = {vertices[i].x_ + t * edge.x_, vertices[i].y_ + t * edge.y_};
    float distSq = (circlePos.x_ - closestPoint.x_) * (circlePos.x_ - closestPoint.x_) +
        (circlePos.y_ - closestPoint.y_) * (circlePos.y_ - closestPoint.y_);
    closestDistSq = std::min(closestDistSq, distSq);
  }
  return closestDistSq <= (circle.GetRadius() * circle.GetRadius());
}
[[nodiscard]] static const bool IsOnePolygonCollidingWithOneCircle(const PhysicalPolygon &polygon,
                                                                   const PhysicalCircle &circle) {
  return IsOneCircleCollidingWithOnePolygon(circle, polygon);
}
}  // namespace physic
#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_MATH_FOR_CIRCLES_H_
