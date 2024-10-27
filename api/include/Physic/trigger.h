//
// Created by Mat on 27.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_TRIGGER_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_TRIGGER_H_

#include "aabb.h"

class Trigger {
 public:

  // TriggerEnter - called when collision begins
  void TriggerEnter(){}

  // TriggerExit - called when collision ends
  void TriggerExit() {}
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_TRIGGER_H_
