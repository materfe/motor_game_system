//
// Created by Mat on 02.10.2024.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Graphic/drawable_shape.h"

class DrawableCircle final : public DrawableShape {
 private:
  float radius_; // Radius of the circle

 public:
  DrawableCircle(const float x, const float y, const float radius) : DrawableShape(x, y), radius_(radius) {};

  //GET
  [[nodiscard]] float getRadius() const { return radius_; };
};

#endif //CIRCLE_H