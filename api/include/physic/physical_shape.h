//
// Created by Mat on 30.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_SHAPE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_SHAPE_H_

#include "vec2.h"

class PhysicalShape
{
 protected:
  core::Vec2<float> position_;        //position
  core::Vec2<float> velocity_ {0.0f, 0.0f};        //velocity in meter per sec
  core::Vec2<float> acceleration_ {0.0f, 0.0f};    //acceleration in meter per second**2
  float mass_;                        //mass in kg


 public:
  PhysicalShape(core::Vec2<float> position, float mass) : position_(position), mass_(mass){};
  PhysicalShape(core::Vec2<float> position, core::Vec2<float> velocity, float mass) : position_(position),
  velocity_(velocity), mass_(mass){};


  //GET
  [[nodiscard]] core::Vec2<float> GetPosition() const {return position_;}
};



#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_SHAPE_H_
