//
// Created by Mat on 24.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_

#include "common.h"
#include "vec2.h"
#include "physical_shape.h"
#include "collider.h"

class AABB : public PhysicalShape {
 private:
  float min_x_bound_ = 0.0f;
  float max_x_bound_ = 0.0f;
  float min_y_bound_ = 0.0f;
  float max_y_bound_ = 0.0f;
  core::Vec2<float> center_{0.0f, 0.0f};
  Collider collider_{};

 public:

  AABB() = default;

  AABB(const float min_x, const float max_x, const float min_y, const float max_y)
      : PhysicalShape(),
        min_x_bound_(min_x),
        max_x_bound_(max_x),
        min_y_bound_(min_y),
        max_y_bound_(max_y) { SetCenter(); }

  AABB(const core::Vec2<float> min_bound, const core::Vec2<float> max_bound)
      : PhysicalShape(), min_x_bound_(min_bound.x_),
        min_y_bound_(min_bound.y_),
        max_x_bound_(max_bound.x_),
        max_y_bound_(max_bound.y_) {
    SetCenter();
  }

  AABB(const core::Vec2<float> min_bound, const core::Vec2<float> max_bound, const core::Vec2<float> velocity)
      : PhysicalShape(velocity),
        min_x_bound_(min_bound.x_),
        min_y_bound_(min_bound.y_),
        max_x_bound_(max_bound.x_),
        max_y_bound_(max_bound.y_) {
    SetCenter();
    mass_ = common::GenerateRandomNumber(1.0f, 5.0f);
  }

  AABB(const core::Vec2<float> min_bound, const core::Vec2<float> max_bound, const core::Vec2<float> velocity, const float mass)
      : PhysicalShape(core::Vec2<float>::Zero(), velocity, mass),
        min_x_bound_(min_bound.x_),
        min_y_bound_(min_bound.y_),
        max_x_bound_(max_bound.x_),
        max_y_bound_(max_bound.y_) {
    SetCenter();
  }

  void UpdatePos(const float min_x, const float max_x, const float min_y, const float max_y);
  void Update(const float delta_time, const float limit_x_bound, const float limit_y_bound);

  void SetCenter();

  //GET
  [[nodiscard]] float GetMinX() const { return min_x_bound_; }
  [[nodiscard]] float GetMaxX() const { return max_x_bound_; }
  [[nodiscard]] float GetMinY() const { return min_y_bound_; }
  [[nodiscard]] float GetMaxY() const { return max_y_bound_; }
  [[nodiscard]] Collider &collider() { return collider_; }
  [[nodiscard]] float width() const {return max_x_bound_ - min_x_bound_;}
  [[nodiscard]] float height() const {return max_y_bound_ - min_y_bound_;}
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_AABB_H_
