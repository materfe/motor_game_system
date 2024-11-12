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
  AABB collider_{GetMinBounds().x_, GetMaxBounds().x_,
                 GetMinBounds().y_, GetMaxBounds().y_};

 public:
  PhysicalPolygon(core::Vec2<float> velocity, float mass, std::vector<core::Vec2<float>> vertices);
  PhysicalPolygon() : PhysicalShape(core::Vec2<float>::Zero(), 0.0f) {}

  void SetPositionToCenter();
  // Get the minimum bounds returns (min x and min y)
  core::Vec2<float> GetMinBounds() const;

  // Get the maximum bounds returns (max x and max y)
  core::Vec2<float> GetMaxBounds() const;

  void Update(const float delta_time, const float max_x_bound, const float max_y_bound);

  //GET
  [[nodiscard]] const std::vector<core::Vec2<float>> & GetVertices() const {return vertices_;}
  [[nodiscard]] AABB& GetCollider() {return collider_;}
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_POLYGON_H_
