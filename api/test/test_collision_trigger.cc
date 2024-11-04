//
// Created by Mat on 24.10.2024.
//


#include <gtest/gtest.h>
#include "Physic/aabb.h"
#include "Physic/physical_polygon.h"
#include "Physic/physical_circle.h"
#include "Physic/intersection_manager.h"
#include <vector>

TEST(trigger_collision_test_suite, two_aabb_colliding) {
  //set three boxes
  AABB box1(2.0f, 4.0f, 1.0f, 3.0f);
  AABB box2(3.0f, 5.0f, 2.0f, 4.0f);
  AABB box3(6.0f, 9.0f, 7.0f, 8.0f);

  const auto result_1 = Physic::AreTwoAabbsColliding(box1, box2);
  const auto result_2 = Physic::AreTwoAabbsColliding(box2, box1);
  const auto result_3 = Physic::AreTwoAabbsColliding(box1, box3);

  EXPECT_EQ(result_1, true);
  EXPECT_EQ(result_2, true);
  EXPECT_EQ(result_3, false);
}

TEST(trigger_collision_test_suite, two_circle_colliding) {
  //set four circles
  PhysicalCircle circle_1(core::Vec2<float>(2.0f, 2.0f), 0.0f, 1.0f);
  PhysicalCircle circle_2(core::Vec2<float>(3.0f, 2.0f), 0.0f, 1.0f);
  PhysicalCircle circle_3(core::Vec2<float>(4.0f, 4.0f), 0.0f, 0.5f);
  PhysicalCircle circle_4(core::Vec2<float>(2.0f, 4.0f), 0.0f, 1.0f);

  const auto result_1 = Physic::AreTwoCirclesColliding(circle_1, circle_2); //true
  const auto result_2 = Physic::AreTwoCirclesColliding(circle_1, circle_3); //false
  const auto result_3 = Physic::AreTwoCirclesColliding(circle_1, circle_4); //true

  EXPECT_EQ(result_1, true);
  EXPECT_EQ(result_2, false);
  EXPECT_EQ(result_3, true);
}

TEST(trigger_collision_test_suite, two_polygon_colliding) {
  //set three polygons

  PhysicalPolygon poly_1(core::Vec2<float>(1.5f, 1.5f), 1.0f,
                         std::vector<core::Vec2<float>>{
                             core::Vec2<float>(1.0f, 1.0f),
                             core::Vec2<float>(2.0f, 1.0f),
                             core::Vec2<float>(2.0f, 2.0f),
                             core::Vec2<float>(1.0f, 2.0f)
                         });
  PhysicalPolygon poly_2 (core::Vec2<float>(2.5f, 2.5f), 1.0f,
                          std::vector<core::Vec2<float>>{
                              core::Vec2<float>(2.0f, 2.0f),
                              core::Vec2<float>(3.0f, 2.0f),
                              core::Vec2<float>(3.0f, 3.0f),
                              core::Vec2<float>(2.0f, 3.0f)
                          });
  PhysicalPolygon poly_3 (core::Vec2<float>(3.5f, 0.5f), 1.0f,
                          std::vector<core::Vec2<float>>{
                              core::Vec2<float>(3.0f, 0.0f),
                              core::Vec2<float>(4.0f, 0.0f),
                              core::Vec2<float>(4.0f, 1.0f),
                              core::Vec2<float>(3.0f, 1.0f)
                          });

  const auto result_1 = Physic::AreTwoPolygonsColliding(poly_1, poly_2); //true
  const auto result_2 = Physic::AreTwoPolygonsColliding(poly_2, poly_1); //true
  const auto result_3 = Physic::AreTwoPolygonsColliding(poly_1, poly_3); //true

  EXPECT_EQ(result_1, true);
  EXPECT_EQ(result_2, true);
  EXPECT_EQ(result_3, false);
}

TEST(trigger_collision_test_suite, aabb_and_polygon_colliding) {
  //set two aabb
  AABB box_1(1.0f, 2.0f, 1.0f, 2.0f);
  AABB box_2(3.0f, 4.0f, 0.0f, 1.0f);
  //set two polygon
  PhysicalPolygon poly_1(core::Vec2<float>(1.5f, 1.5f), 1.0f,
                         std::vector<core::Vec2<float>>{
                             core::Vec2<float>(2.0f, 2.0f),
                             core::Vec2<float>(3.0f, 2.0f),
                             core::Vec2<float>(2.0f, 3.0f)
                         });
  PhysicalPolygon poly_2 (core::Vec2<float>(2.5f, 2.5f), 1.0f,
                          std::vector<core::Vec2<float>>{
                              core::Vec2<float>(0.0f, 3.0f),
                              core::Vec2<float>(1.0f, 3.0f),
                              core::Vec2<float>(0.0f, 4.0f)
                          });

  const auto result_1 = Physic::IsOneAabbCollidingWithOnePolygon(box_1, poly_1); //true
  const auto result_1_reverse = Physic::IsOnePolygonCollidingWithOneAabb(poly_1, box_1); //true

  const auto result_2 = Physic::IsOnePolygonCollidingWithOneAabb(poly_1, box_2); //false
  const auto result_2_reverse = Physic::IsOneAabbCollidingWithOnePolygon(box_2, poly_1); //false

  const auto result_3 = Physic::IsOnePolygonCollidingWithOneAabb(poly_2, box_1); //false
  const auto result_3_reverse =  Physic::IsOneAabbCollidingWithOnePolygon(box_1, poly_2); //false

  EXPECT_EQ(result_1, true);
  EXPECT_EQ(result_1_reverse, true);
  EXPECT_EQ(result_2, false);
  EXPECT_EQ(result_2_reverse, false);
  EXPECT_EQ(result_3, false);
  EXPECT_EQ(result_3_reverse, false);
}

TEST(trigger_collision_test_suite, circle_and_aabb_colliding) {
  //set two circles
  PhysicalCircle circle_1(core::Vec2<float>(3.0f, 2.0f), 0.0f, 1.0f);
  PhysicalCircle circle_2(core::Vec2<float>(1.0f, 4.0f), 0.0f, 1.0f);
  //set two aabb
  AABB box_1(1.0f, 2.0f, 1.0f, 2.0f);
  AABB box_2(3.0f, 4.0f, 0.0f, 1.0f);

  const auto result_1 = Physic::IsOneCircleCollidingWithOneAabb(circle_1, box_1); //true
  const auto result_1_reverse = Physic::IsOneAabbCollidingWithOneCircle(box_1, circle_1); //true

  const auto result_2 = Physic::IsOneCircleCollidingWithOneAabb(circle_1, box_2); //true
  const auto result_2_reverse = Physic::IsOneAabbCollidingWithOneCircle(box_2, circle_1); //true

  const auto result_3 = Physic::IsOneCircleCollidingWithOneAabb(circle_2, box_1); //false
  const auto result_3_reverse = Physic::IsOneAabbCollidingWithOneCircle(box_1, circle_2); //false

  EXPECT_EQ(result_1, true);
  EXPECT_EQ(result_1_reverse, true);
  EXPECT_EQ(result_2, true);
  EXPECT_EQ(result_2_reverse, true);
  EXPECT_EQ(result_3, false);
  EXPECT_EQ(result_3_reverse, false);
}

TEST(trigger_collision_test_suite, circle_and_polygon_colliding) {
  //set two circles
  PhysicalCircle circle_1(core::Vec2<float>(2.0f, 1.0f), 0.0f, 1.0f);
  PhysicalCircle circle_2(core::Vec2<float>(4.0f, 4.0f), 0.0f, 1.0f);
  //set two polygon
  PhysicalPolygon poly_1(core::Vec2<float>(1.5f, 1.5f), 1.0f,
                         std::vector<core::Vec2<float>>{
                             core::Vec2<float>(2.0f, 2.0f),
                             core::Vec2<float>(3.0f, 2.0f),
                             core::Vec2<float>(2.0f, 3.0f)
                         });
  PhysicalPolygon poly_2 (core::Vec2<float>(2.5f, 2.5f), 1.0f,
                          std::vector<core::Vec2<float>>{
                              core::Vec2<float>(0.0f, 3.0f),
                              core::Vec2<float>(1.0f, 3.0f),
                              core::Vec2<float>(0.0f, 4.0f)
                          });

  const auto result_1 = Physic::IsOneCircleCollidingWithOnePolygon(circle_1, poly_1); //true
  const auto result_1_reverse = Physic::IsOnePolygonCollidingWithOneCircle(poly_1, circle_1); //true

  const auto result_2 = Physic::IsOneCircleCollidingWithOnePolygon(circle_1, poly_2); //false
  const auto result_2_reverse = Physic::IsOnePolygonCollidingWithOneCircle(poly_2, circle_1); //false

  const auto result_3 = Physic::IsOneCircleCollidingWithOnePolygon(circle_2, poly_1); //false
  const auto result_3_reverse = Physic::IsOnePolygonCollidingWithOneCircle(poly_1, circle_2); //false

  EXPECT_EQ(result_1, true);
  EXPECT_EQ(result_1_reverse, true);
  EXPECT_EQ(result_2, false);
  EXPECT_EQ(result_2_reverse, false);
  EXPECT_EQ(result_3, false);
  EXPECT_EQ(result_3_reverse, false);
}