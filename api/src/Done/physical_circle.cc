//
// Created by Mat on 30.10.2024.
//


#include "Done/physical_circle.h"

PhysicalCircle::PhysicalCircle(core::Vec2<float> position, float mass, float radius) : PhysicalShape(position, mass),
radius_(radius){}

AABB PhysicalCircle::GetAABB() const {
  const float minX = position_.x_ - radius_;
  const float minY = position_.y_ - radius_;
  const float maxX = position_.x_ + radius_;
  const float maxY = position_.y_ + radius_;

  return AABB(minX, maxX, minY, maxY);
}