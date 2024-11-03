//
// Created by Mat on 22.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_DRAWABLE_SHAPE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_DRAWABLE_SHAPE_H_

#include "vec2.h"
#include <array>


class DrawableShape {
 protected:
  core::Vec2<float> position_;
  std::array<int, 4> color_; //TODO dont use int its too much, distinguish physic and graphic

 public:

  explicit DrawableShape(core::Vec2<float> position) : position_(position), color_({}) {};
  explicit DrawableShape(float x, float y) : position_(x, y), color_({}) {};

  //if you want to create a random color just for the current object
  void SetRandomColor();


  //GET
  [[nodiscard]] core::Vec2<float> getPosition() {return position_;}
  [[nodiscard]] std::array<int, 4> getColor() {return color_;}
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_DRAWABLE_SHAPE_H_
