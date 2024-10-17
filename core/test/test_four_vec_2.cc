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

  const auto result = vec_1 + vec_2;

  EXPECT_FLOAT_EQ(result.GetX()[0], 5.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 7.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 9.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 11.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], 5.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], 7.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], 9.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], 11.0f);
}


TEST(test_four_vec_2, subtract) {
  std::array<float, 4> all_x_values{7.0f, 6.0f, 5.0f, 4.0f};
  std::array<float, 4> all_y_values{4.0f, 3.0f, 2.0f, 1.0f};
  const auto vec_1 = core::FourVec2<float>(all_x_values, all_y_values);
  const auto vec_2 = core::FourVec2<float>(all_y_values, all_x_values);

  const auto result = vec_1 - vec_2;

  EXPECT_FLOAT_EQ(result.GetX()[0], 3.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 3.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 3.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 3.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], -3.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], -3.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], -3.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], -3.0f);
}


TEST(test_four_vec_2, multiply_scalar) {
  std::array<float, 4> all_x_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_y_values{2.0f, 3.0f, 4.0f, 5.0f};
  const auto vec_1 = core::FourVec2<float>(all_x_values, all_y_values);

  const float scalar = 2.0f;
  const auto result = vec_1 * scalar;

  EXPECT_FLOAT_EQ(result.GetX()[0], 2.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 4.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 6.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 8.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], 4.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], 6.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], 8.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], 10.0f);
}


TEST(test_four_vec_2, divide_scalar) {
  std::array<float, 4> all_x_values{2.0f, 4.0f, 6.0f, 8.0f};
  std::array<float, 4> all_y_values{4.0f, 6.0f, 8.0f, 10.0f};
  const auto vec_1 = core::FourVec2<float>(all_x_values, all_y_values);

  const float scalar = 2.0f;
  const auto result = vec_1 / scalar;

  EXPECT_FLOAT_EQ(result.GetX()[0], 1.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 2.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 3.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 4.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], 2.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], 3.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], 4.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], 5.0f);
}


TEST(test_four_vec_2, magnitude) {
  std::array<float, 4> all_x_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_y_values{1.0f, 2.0f, 3.0f, 4.0f};
  const auto vec_1 = core::FourVec2<float>(all_x_values, all_y_values);

  const std::array<float, 4> magnitude = vec_1.Magnitude();
  EXPECT_FLOAT_EQ(magnitude[0], std::sqrt(2.0f));
  EXPECT_FLOAT_EQ(magnitude[1], std::sqrt(8.0f));
  EXPECT_FLOAT_EQ(magnitude[2], std::sqrt(18.0f));
  EXPECT_FLOAT_EQ(magnitude[3], std::sqrt(32.0f));
}


TEST(test_four_vec_2, sqr_magnitude) {
  std::array<float, 4> all_x_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_y_values{1.0f, 2.0f, 3.0f, 4.0f};
  const auto vec_1 = core::FourVec2<float>(all_x_values, all_y_values);

  const std::array<float, 4> sqr_magnitude = vec_1.SqrtMagnitude();
  EXPECT_FLOAT_EQ(sqr_magnitude[0], 2.0f);
  EXPECT_FLOAT_EQ(sqr_magnitude[1], 8.0f);
  EXPECT_FLOAT_EQ(sqr_magnitude[2], 18.0f);
  EXPECT_FLOAT_EQ(sqr_magnitude[3], 32.0f);
}


TEST(test_four_vec_2, normalise) {
  std::array<float, 4> all_x_values{3.0f, 0.0f, 4.0f, 0.0f};
  std::array<float, 4> all_y_values{0.0f, 1.0f, 0.0f, 1.0f};
  auto vec_1 = core::FourVec2<float>(all_x_values, all_y_values);

  const auto result = vec_1.Normalise();

  EXPECT_FLOAT_EQ(result.GetX()[0], 1.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 0.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 1.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 0.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], 0.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], 1.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], 0.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], 1.0f);
}