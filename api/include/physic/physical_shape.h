﻿//
// Created by Mat on 30.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_SHAPE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_SHAPE_H_

#include "vec2.h"

class PhysicalShape
{
 protected:
  core::Vec2<float> position_{0.0f, 0.0f};        //position
  core::Vec2<float> velocity_ {0.0f, 0.0f};        //velocity in meter per sec
  core::Vec2<float> acceleration_ {0.0f, 0.0f};    //acceleration in meter per second**2
  float mass_ = 0.0f;                        //mass in kg


 public:
  PhysicalShape(core::Vec2<float> position, float mass) : position_(position), mass_(mass){};
  PhysicalShape(core::Vec2<float> position, core::Vec2<float> velocity, float mass) : position_(position),
  velocity_(velocity), mass_(mass){};
  PhysicalShape() = default;
  PhysicalShape(core::Vec2<float> velocity) : velocity_(velocity){}


  //GET
  [[nodiscard]] core::Vec2<float> GetPosition() const {return position_;}
  [[nodiscard]] core::Vec2<float>& GetVelocity() {return velocity_;}
  [[nodiscard]] float GetMass() const {return mass_;}

  //SET
  void SetVelocity(const float x, const float y){velocity_.x_ = x, velocity_.y_ = y;}
};



#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_SHAPE_H_
