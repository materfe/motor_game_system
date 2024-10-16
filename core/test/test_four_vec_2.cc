//
// Created by Mat on 16.10.2024.
//

#include <gtest/gtest.h>
#include "four_vec2.h"

TEST(test_four_vec_2, add) {
  std::array<float, 4> all_x_values{4.0f, 5.0f, 6.0f, 7.0f};
  std::array<float, 4> all_y_values{1.0f, 2.0f, 3.0f, 4.0f};
  const auto vec_1 = core::FourVec2<float>(all_x_values, all_y_values);
  const auto vec_2 = core::FourVec2<float>(all_y_values, all_x_values);

  EXPECT_FLOAT_EQ(vec_1.GetX()[0], 4.0f);
  EXPECT_FLOAT_EQ(vec_1.GetX()[1], 5.0f);
  EXPECT_FLOAT_EQ(vec_1.GetX()[2], 6.0f);
  EXPECT_FLOAT_EQ(vec_1.GetX()[3], 7.0f);

  const auto result = vec_1 + vec_2;

  EXPECT_FLOAT_EQ(result.GetX()[0], 5.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 7.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 9.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 11.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], 5.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], 7.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], 9.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], 11.0f);
};