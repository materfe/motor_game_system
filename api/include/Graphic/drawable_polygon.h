//
// Created by Mat on 22.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_POLYGON_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_POLYGON_H_

#include "Graphic/drawable_shape.h"
#include <vector>

class DrawablePolygon final : public DrawableShape {
 private:
  std::vector<core::Vec2<float>> vertices_;

 public:

  DrawablePolygon(const float x, const float y, const std::vector<core::Vec2<float>> &vertices)
      : DrawableShape(x, y), vertices_(vertices) {};

  DrawablePolygon(const std::vector<core::Vec2<float>> &vertices)
      : DrawableShape(0.0f, 0.0f), vertices_(vertices) {};


  void Update();

  //GET
  [[nodiscard]] const std::vector<core::Vec2<float>> &getVertices() const { return vertices_; }
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_POLYGON_H_
