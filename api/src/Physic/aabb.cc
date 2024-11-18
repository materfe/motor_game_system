//
// Created by Mat on 24.10.2024.
//

#include "physic/aabb.h"

void AABB::UpdatePos(const float min_x, const float max_x, const float min_y, const float max_y) {
  min_x_bound_ = min_x;
  min_y_bound_ = min_y;
  max_x_bound_ = max_x;
  max_y_bound_ = max_y;
}

void AABB::SetCenter() {
  core::Vec2<float> halfSize = core::Vec2<float>(max_x_bound_ - min_x_bound_,
                                                 max_y_bound_ - min_y_bound_) * 0.5f;
  core::Vec2<float> center = core::Vec2<float>(max_x_bound_ - min_x_bound_,
                                               max_y_bound_ - min_y_bound_) + halfSize;
  center_ = center;
  position_ = center;
}

void AABB::Update(const float delta_time, const float limit_x_bound, const float limit_y_bound) {
  if(max_x_bound_ >= limit_x_bound)
  {
    velocity_.x_ *= -1.0f;
  }
  else if (min_x_bound_ <= 0)
  {
    velocity_.x_ *= -1.0f;
  }
  if(max_y_bound_ >= limit_y_bound)
  {
    velocity_.y_ *= -1.0f;
  }
  else if (min_y_bound_ <= 0)
  {
    velocity_.y_ *= -1.0f;
  }

  min_x_bound_ += velocity_.x_ * delta_time;
  max_x_bound_ += velocity_.x_ * delta_time;
  min_y_bound_ += velocity_.y_ * delta_time;
  max_y_bound_ += velocity_.y_ * delta_time;
  SetCenter();
}