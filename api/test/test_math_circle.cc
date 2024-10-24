//
// Created by Mat on 23.10.2024.
//


#include <gtest/gtest.h>
#include "Physic/math_for_circles.h"
#include "vec2.h"

TEST(test_math_circles, test_colliding)
{
  //first circle
  const core::Vec2<float> position1(15.0f, 40.0f);
  const float radius1 = 15.0f;

  //second circle
  const core::Vec2<float> position2(35.0f, 40.0f);
  float radius2 = 5.0f;

  CircleMath math_circle;
  auto result = math_circle.AreCirclesColliding(position1, radius1, position2, radius2);

  EXPECT_EQ(result, true); //should collide

  //swap a radius value -> should not collide
  radius2 = 2.0f;
  result = math_circle.AreCirclesColliding(position1, radius1, position2, radius2);

  EXPECT_EQ(result, false);
}


TEST(test_math_circles, test_overlapping)
{
  //first circle
  const core::Vec2<float> position1(15.0f, 40.0f);
  const float radius1 = 15.0f;

  //second circle
  const core::Vec2<float> position2(22.0f, 40.0f);
  float radius2 = 7.0f;

  CircleMath math_circle;
  auto result = math_circle.AreCirclesOverlapping(position1, radius1, position2, radius2);

  EXPECT_EQ(result, true); //should overlap

  //swap a radius value -> should not overlap
  radius2 = 10.0f;
  result = math_circle.AreCirclesOverlapping(position1, radius1, position2, radius2);

  EXPECT_EQ(result, false);
}