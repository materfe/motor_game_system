//
// Created by Mat on 14.11.2024.
//

#include "physic/collider.h"

void Collider::OnTriggerEnter() {
  is_trigger_= true;
}
void Collider::OnTriggerExit() {
  is_trigger_ = false;
}