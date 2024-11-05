//
// Created by Mat on 05.11.2024.
//

//
// Created by Mat on 24.10.2024.
//


#include <gtest/gtest.h>
#include "physic/physical_circle.h"
#include "physic/contact_listener.h"
#include <vector>

TEST(contact_listener_test_suite, two_circles_colliding) {
  ContactListener listener;

  PhysicalCircle circle_1(core::Vec2<float>(2.0f, 2.0f), 2.0f, 1.0f);
  PhysicalCircle circle_2(core::Vec2<float>(3.0f, 2.0f), 2.0f, 1.0f);
  PhysicalCircle circle_3(core::Vec2<float>(30.0f, 2.0f), 2.0f, 1.0f);

  auto result = listener.GetSet();
  EXPECT_EQ(result.size(), 0);

  listener.updateContact(circle_1, circle_2);
  result = listener.GetSet();
  EXPECT_EQ(result.size(), 1);

  listener.updateContact(circle_1, circle_3);
  result = listener.GetSet();
  EXPECT_EQ(result.size(), 1);
}