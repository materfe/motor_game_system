//
// Created by Mat on 24.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_

#include "Graphic/drawable_polygon.h"
#include <array>

class AABB {
 private:
  float min_x_bound_;
  float max_x_bound_;
  float min_y_bound_;
  float max_y_bound_;

 public:

  AABB()
  {
    min_x_bound_ = 0.0f;
    max_x_bound_ = 0.0f;
    min_y_bound_ = 0.0f;
    max_y_bound_ = 0.0f;
  };

  AABB(const float min_x, const float max_x, const float min_y, const float max_y)
      : min_x_bound_(min_x), max_x_bound_(max_x), min_y_bound_(min_y), max_y_bound_(max_y) {}



  //GET
  [[nodiscard]] float getMinX() const { return min_x_bound_; }
  [[nodiscard]] float getMaxX() const { return max_x_bound_; }
  [[nodiscard]] float getMinY() const { return min_y_bound_; }
  [[nodiscard]] float getMaxY() const { return max_y_bound_; }
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_
