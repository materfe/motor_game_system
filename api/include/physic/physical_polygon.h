//
// Created by Mat on 30.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_POLYGON_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_POLYGON_H_

#include "physical_shape.h"
#include "aabb.h"
#include <vector>

class PhysicalPolygon final : public PhysicalShape {
 private:
  std::vector<core::Vec2<float>> vertices_;

 public:
  PhysicalPolygon(core::Vec2<float> position, float mass, std::vector<core::Vec2<float>> vertices);



  //GET
  [[nodiscard]] const std::vector<core::Vec2<float>> & GetVertices() const {return vertices_;}
  [[nodiscard]] AABB GetAABB() const;
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_POLYGON_H_
