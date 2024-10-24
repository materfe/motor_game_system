//
// Created by Mat on 22.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_SHAPE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_SHAPE_H_

#include <array>
#include "vec2.h"

class Shape {
 protected:
  core::Vec2<float> position_;
  std::array<int, 4> color_;

 public:

  explicit Shape(core::Vec2<float> position) : position_(position), color_({}) {};
  explicit Shape(float x, float y) : position_(x, y), color_({}) {};

  //if you want to create a random color just for the current object
  void SetRandomColor();


  //GET
  [[nodiscard]] core::Vec2<float> getPosition() {return position_;}
  [[nodiscard]] std::array<int, 4> getColor() {return color_;}
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_SHAPE_H_
