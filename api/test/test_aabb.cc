//
// Created by Mat on 24.10.2024.
//


#include <gtest/gtest.h>
#include "Physic/aabb.h"
#include "Physic/polygon.h"

TEST(aabb_test_suite, colliding) {
  //set three boxes
  AABB box1(2.0f, 4.0f, 1.0f, 3.0f);
  AABB box2(3.0f, 5.0f, 2.0f, 4.0f);
  AABB box3(6.0f, 9.0f, 7.0f, 8.0f);

  const auto result_1 = box1.IsColliding(box2);
  const auto result_2 = box2.IsColliding(box1);
  const auto result_3 = box1.IsColliding(box3);

  EXPECT_EQ(result_1, true);
  EXPECT_EQ(result_2, true);
  EXPECT_EQ(result_3, false);
}

TEST(aabb_test_suite, colliding_with_pollygon) {
  //set three boxes
  AABB box1(2.0f, 4.0f, 1.0f, 3.0f);
  AABB box2(6.0f, 9.0f, 7.0f, 8.0f);
  AABB box3(7.0f, 9.0f, 3.0f, 5.0f);

  std::vector<core::Vec2<float>> vertices = {
      {3.0f, 2.0f},
      {3.0f, 4.0f},
      {5.0f, 6.0f},
      {7.0f, 5.0f},
      {6.0f, 3.0f},
      {5.0f, 2.0f},
  };
  Polygon poly(6, vertices);

  const auto result_1 = box1.IsCollidingWithPolygon(poly);
  const auto result_2 = box2.IsCollidingWithPolygon(poly);
  const auto result_3 = box3.IsCollidingWithPolygon(poly);

  EXPECT_EQ(result_1, true);
  EXPECT_EQ(result_2, false);
  EXPECT_EQ(result_3, true);
}