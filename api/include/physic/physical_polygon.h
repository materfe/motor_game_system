//
// Created by Mat on 30.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_POLYGON_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_POLYGON_H_

#include "physical_shape.h"
#include "aabb.h"
#include "common.h"
#include <vector>

class PhysicalPolygon final : public PhysicalShape {
 private:
  std::vector<core::Vec2<float>> vertices_;
  AABB bounds_{};

 public:
  PhysicalPolygon(core::Vec2<float> velocity, float mass, std::vector<core::Vec2<float>> vertices);
  PhysicalPolygon() : PhysicalShape(core::Vec2<float>::Zero(), 0.0f) {
    bounds_.UpdatePos(GetMinBounds().x_, GetMaxBounds().x_, GetMinBounds().x_, GetMaxBounds().y_);
  }

  void SetPositionToCenter();
  // Get the minimum bounds returns (min x and min y)
  core::Vec2<float> GetMinBounds() const;

  // Get the maximum bounds returns (max x and max y)
  core::Vec2<float> GetMaxBounds() const;

  void Update(const float delta_time, const float max_x_bound, const float max_y_bound);

  // Function to create convex hull from a set of points
  std::vector<core::Vec2<float>> GenerateConvexHull(std::vector<core::Vec2<float>> points) {
    if (points.size() < 3) return points; // A polygon requires at least 3 points

    // Sort points lexicographically by x (then by y)
    std::sort(points.begin(), points.end(), [](const core::Vec2<float>& a, const core::Vec2<float>& b) {
      return a.x_ < b.x_ || (a.x_ == b.x_ && a.y_ < b.y_);
    });

    std::vector<core::Vec2<float>> hull;

    // Build lower hull
    for (const auto& point : points) {
      while (hull.size() >= 2 && common::CrossProduct(hull[hull.size() - 2], hull[hull.size() - 1], point) <= 0) {
        hull.pop_back();
      }
      hull.push_back(point);
    }

    // Build upper hull
    size_t lowerHullSize = hull.size();
    for (int i = points.size() - 2; i >= 0; i--) {
      while (hull.size() > lowerHullSize && common::CrossProduct(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0) {
        hull.pop_back();
      }
      hull.push_back(points[i]);
    }

    hull.pop_back(); // Remove the last point because it’s the same as the first

    return hull; // Now `hull` contains the vertices in convex order
  }

  //GET
  [[nodiscard]] const std::vector<core::Vec2<float>> & GetVertices() const {return vertices_;}
  [[nodiscard]] AABB& bounds() {return bounds_;}
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_POLYGON_H_
