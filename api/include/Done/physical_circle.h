//
// Created by Mat on 30.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_

#include "physical_shape.h"
#include "aabb.h"

class PhysicalCircle final : public PhysicalShape
{
 private:
  float radius_;

 public:
  PhysicalCircle(core::Vec2<float> position, float mass, float radius);


  //GET
  [[nodiscard]] float GetRadius() const {return radius_;}
  [[nodiscard]] AABB GetAABB() const;
};


#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_
