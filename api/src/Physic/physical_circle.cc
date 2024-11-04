//
// Created by Mat on 30.10.2024.
//


#include "Physic/physical_circle.h"

void PhysicalCircle::Update(const float delta_time, const float max_x_bound, const float max_y_bound) {

  if(position_.x_ + radius_ >= max_x_bound)
  {
    position_.x_ = max_x_bound - radius_;
    velocity_.x_ *= -1.0f;
  }
  else if (position_.x_ - radius_ <= 0)
  {
    position_.x_ = 0.0f + radius_;
    velocity_.x_ *= -1.0f;
  }
  if(position_.y_ + radius_ >= max_y_bound)
  {
    position_.y_ = max_y_bound - radius_;
    velocity_.y_ *= -1.0f;
  }
  else if (position_.y_ - radius_ <= 0)
  {
    position_.y_ = 0.0f + radius_;
    velocity_.y_ *= -1.0f;
  }


  position_.x_ += velocity_.x_ * delta_time;
  position_.y_ += velocity_.y_ * delta_time;

  collider_.UpdatePos(position_.x_ - radius_, position_.x_ + radius_,
                      position_.y_ - radius_, position_.y_ + radius_);
}

