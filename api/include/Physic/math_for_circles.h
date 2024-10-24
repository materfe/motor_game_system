//
// Created by Mat on 23.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_SRC_PHYSIC_MATH_FOR_CIRCLES_H_
#define GAME_MOTOR_ENGINE_API_SRC_PHYSIC_MATH_FOR_CIRCLES_H_

#include "vec2.h"
#include <cmath>

class CircleMath {
 public:

  // Function to check if two circles collide (touch or intersect)
  bool AreCirclesColliding(const core::Vec2<float> &center1, float radius1,
                           const core::Vec2<float> &center2, float radius2);

  // Function to check if two circles overlap (strictly inside one another, excluding just touching)
  bool AreCirclesOverlapping(const core::Vec2<float> &center1, float radius1,
                             const core::Vec2<float> &center2, float radius2);
};

#endif //GAME_MOTOR_ENGINE_API_SRC_PHYSIC_MATH_FOR_CIRCLES_H_
