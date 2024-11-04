//
// Created by Mat on 30.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_

#include "physical_shape.h"
#include "aabb.h"

class PhysicalCircle final : public PhysicalShape {
 private:
  float radius_;
  AABB collider_{position_.x_ - radius_, position_.x_ + radius_,
                 position_.y_ - radius_, position_.y_ + radius_};

 public:
  PhysicalCircle(core::Vec2<float> position, float mass, float radius) : PhysicalShape(position, mass),
                                                                         radius_(radius) {};
  PhysicalCircle(core::Vec2<float> position, core::Vec2<float> velocity, float mass, float radius) :
      PhysicalShape(position, velocity, mass), radius_(radius) {};
  PhysicalCircle() : PhysicalShape(core::Vec2<float>::Zero(), 0.0f), radius_(0.0f) {}



  void Update(const float delta_time, const float max_x_bound, const float max_y_bound);

  //GET
  [[nodiscard]] float GetRadius() const { return radius_; }
  [[nodiscard]] AABB &GetCollider() { return collider_; }
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_
