//
// Created by Mat on 24.10.2024.
//

#include "Physic/aabb.h"

void AABB::UpdatePos(const float min_x, const float max_x, const float min_y, const float max_y) {
  min_x_bound_ = min_x;
  min_y_bound_ = min_y;
  max_x_bound_ = max_x;
  max_y_bound_ = max_y;
}

void AABB::OnTriggerEnter(){
  is_trigger_activated_ = true;
}
void AABB::OnTriggerExit() {
  is_trigger_activated_ = false;
}