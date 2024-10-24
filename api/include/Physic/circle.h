//
// Created by Mat on 02.10.2024.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle final : public Shape {
 private:
  float radius_; // Radius of the circle
  core::Vec2<float> velocity_;

 public:

  Circle(const float x, const float y, const float radius) : Shape(x, y), radius_(radius), velocity_(0.0f, 0.0f) {};

  void Update(float deltatime);

  //update the position based on velocity and delta time
  void MovePosition(float deltatime);

  //GET
  [[nodiscard]] float getRadius() const { return radius_; };
};

#endif //CIRCLE_H