//
// Created by Mat on 23.10.2024.
//

#include "Physic/math_for_circles.h"

bool CircleMath::AreCirclesColliding(const core::Vec2<float> &center1, const float radius1,
                                     const core::Vec2<float> &center2, const float radius2) {
  // Calculate the squared distance between the two centers
  const float deltaX = center2.x_ - center1.x_;
  const float deltaY = center2.y_ - center1.y_;
  const float distanceSquared = deltaX * deltaX + deltaY * deltaY;

  // Calculate the sum of the radi (collision happens if the distance between centers <= sum of radi)
  const float radiSum = radius1 + radius2;
  return distanceSquared <= radiSum * radiSum;

}

bool CircleMath::AreCirclesOverlapping(const core::Vec2<float> &center1, const float radius1,
                                       const core::Vec2<float> &center2, const float radius2) {
  // Calculate the squared distance between the two centers
  const float deltaX = center2.x_ - center1.x_;
  const float deltaY = center2.y_ - center1.y_;
  const float distanceSquared = deltaX * deltaX + deltaY * deltaY;

  // Calculate the difference of the radi (overlap happens if the distance between centers < absolute difference of radii)
  const float radiDifference = std::abs(radius1 - radius2);
  return distanceSquared < radiDifference * radiDifference;
}