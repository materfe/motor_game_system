//
// Created by Mat on 30.10.2024.
//

#include "physic/physical_polygon.h"


PhysicalPolygon::PhysicalPolygon(core::Vec2<float> velocity, float mass, std::vector<core::Vec2<float>> vertices) :
PhysicalShape(core::Vec2<float>::Zero(), velocity, mass), vertices_(vertices)
{
  vertices_ = GenerateConvexHull(vertices);
  SetPositionToCenter();
  bounds_.UpdatePos(GetMinBounds().x_, GetMaxBounds().x_, GetMinBounds().x_, GetMaxBounds().y_);
}

void PhysicalPolygon::SetPositionToCenter() {
  if (vertices_.empty()) return;

  float sumX = 0.0f;
  float sumY = 0.0f;

  // Sum up all vertex coordinates
  for (const auto& vertex : vertices_) {
    sumX += vertex.x_;
    sumY += vertex.y_;
  }

  // Calculate the centroid
  position_.x_ = sumX / static_cast<float>(vertices_.size());
  position_.y_ = sumY / static_cast<float>(vertices_.size());
}

core::Vec2<float> PhysicalPolygon::GetMinBounds() const {
  float minX = std::numeric_limits<float>::max();
  float minY = std::numeric_limits<float>::max();

  for (const auto& vertex : vertices_) {
    if (vertex.x_ < minX) minX = vertex.x_;
    if (vertex.y_ < minY) minY = vertex.y_;
  }

  return {minX, minY};
}

core::Vec2<float> PhysicalPolygon::GetMaxBounds() const {
  float maxX = std::numeric_limits<float>::lowest();
  float maxY = std::numeric_limits<float>::lowest();

  for (const auto& vertex : vertices_) {
    if (vertex.x_ > maxX) maxX = vertex.x_;
    if (vertex.y_ > maxY) maxY = vertex.y_;
  }

  return {maxX, maxY};
}

void PhysicalPolygon::Update(const float delta_time, const float max_x_bound, const float max_y_bound) {
  if(GetMaxBounds().x_ >= max_x_bound)
  {
    velocity_.x_ *= -1.0f;
  }
  else if (GetMinBounds().x_ <= 0)
  {
    velocity_.x_ *= -1.0f;
  }
  if(GetMaxBounds().y_ >= max_y_bound)
  {
    velocity_.y_ *= -1.0f;
  }
  else if (GetMinBounds().y_ <= 0)
  {
    velocity_.y_ *= -1.0f;
  }

  for(auto& v : vertices_)
  {
    v.x_ += velocity_.x_ * delta_time;
    v.y_ += velocity_.y_ * delta_time;
  }
  SetPositionToCenter();

  bounds_.UpdatePos(GetMinBounds().x_, GetMaxBounds().x_,
                      GetMinBounds().y_, GetMaxBounds().y_);
}