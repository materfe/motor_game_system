//
// Created by Mat on 02.10.2024.
//

#include "Physic/circle.h"

void Circle::Update(const float deltatime) {
  SetRandomColor();

  MovePosition(deltatime);
}
void Circle::MovePosition(const float deltatime) {
  position_.x_ = velocity_.x_ * deltatime;
  position_.y_ = velocity_.y_ * deltatime;
}
