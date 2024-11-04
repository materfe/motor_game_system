//
// Created by Mat on 30.10.2024.
//

#include "Physic/physical_polygon.h"


PhysicalPolygon::PhysicalPolygon(core::Vec2<float> position, float mass, std::vector<core::Vec2<float>> vertices) :
PhysicalShape(position, mass), vertices_(vertices)
{}

AABB PhysicalPolygon::GetAABB() const{
  float minX = std::numeric_limits<float>::max();
  float minY = std::numeric_limits<float>::max();
  float maxX = std::numeric_limits<float>::lowest();
  float maxY = std::numeric_limits<float>::lowest();

  // Iterate through all vertices to find min/max x and y values
  for (const auto& vertex : vertices_) {
    minX = std::min(minX, vertex.x_);
    minY = std::min(minY, vertex.y_);
    maxX = std::max(maxX, vertex.x_);
    maxY = std::max(maxY, vertex.y_);
  }

  // Create and return the AABB from these bounds
  return AABB(minX, maxX, minY, maxY);
}