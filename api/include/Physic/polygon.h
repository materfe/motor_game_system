//
// Created by Mat on 22.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_POLYGON_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_POLYGON_H_

#include "shape.h"
#include <vector>

class Polygon final : public Shape {
 private:
  int number_of_sides_; // number of sides of the polygon
  std::vector<core::Vec2<float>> vertices_;

 public:

  Polygon(const float x, const float y, const int number_of_side, const std::vector<core::Vec2<float>> &vertices)
      : Shape(x, y), number_of_sides_(number_of_side), vertices_(vertices) {};

  Polygon(const int number_of_side, const std::vector<core::Vec2<float>> &vertices)
      : Shape(0.0f, 0.0f), number_of_sides_(number_of_side), vertices_(vertices) {};


  void Update();

  //GET
  [[nodiscard]] int getSides() const { return number_of_sides_; }
  [[nodiscard]] const std::vector<core::Vec2<float>> &getVertices() const { return vertices_; }
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_POLYGON_H_
