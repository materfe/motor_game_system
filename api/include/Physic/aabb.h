//
// Created by Mat on 24.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_

#include "polygon.h"
#include <array>

class AABB {
 private:
  float min_x_bound_;
  float max_x_bound_;
  float min_y_bound_;
  float max_y_bound_;

  // Method to project a point onto an axis
  float ProjectPoint(const core::Vec2<float> &point, const core::Vec2<float> &axis) const {
    return point.x_ * axis.x_ + point.y_ * axis.y_;
  }

  // Method to check if projections of both the AABB and Polygon overlap on a given axis
  [[nodiscard]] bool OverlapOnAxis(const core::Vec2<float> &axis,
                                   const std::vector<core::Vec2<float>> &vertices) const;

 public:

  AABB(const float min_x, const float max_x, const float min_y, const float max_y)
      : min_x_bound_(min_x), max_x_bound_(max_x), min_y_bound_(min_y), max_y_bound_(max_y) {}

  // Method to check if this AABB overlaps/collides with another AABB
  [[nodiscard]] bool IsColliding(const AABB &other) const;

  // Method to check if this AABB is colliding with a Polygon
  [[nodiscard]] bool IsCollidingWithPolygon(Polygon &polygon) const;

  // GET
  //[[nodiscard]] float getMinX() const { return min_x_bound_; }
  //[[nodiscard]] float getMaxX() const { return max_x_bound_; }
  //[[nodiscard]] float getMinY() const { return min_y_bound_; }
  //[[nodiscard]] float getMaxY() const { return max_y_bound_; }
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_
