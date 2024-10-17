//
// Created by Mat on 16.10.2024.
//


#include <gtest/gtest.h>
#include "four_vec_3.h"


TEST(test_four_vec_3, add) {
  std::array<float, 4> all_x_values{4.0f, 5.0f, 6.0f, 7.0f};
  std::array<float, 4> all_y_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_z_values{7.0f, 6.0f, 5.0f, 4.0f};

  const auto vec_1 = core::FourVec3<float>(all_x_values, all_y_values, all_z_values);
  const auto vec_2 = core::FourVec3<float>(all_y_values, all_x_values, all_z_values); // Test adding Z too

  const auto result = vec_1 + vec_2;

  EXPECT_FLOAT_EQ(result.GetX()[0], 5.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 7.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 9.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 11.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], 5.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], 7.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], 9.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], 11.0f);

  EXPECT_FLOAT_EQ(result.GetZ()[0], 14.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[1], 12.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[2], 10.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[3], 8.0f);
}


TEST(test_four_vec_3, subtract) {
  std::array<float, 4> all_x_values{7.0f, 6.0f, 5.0f, 4.0f};
  std::array<float, 4> all_y_values{4.0f, 3.0f, 2.0f, 1.0f};
  std::array<float, 4> all_z_values{3.0f, 2.0f, 1.0f, 0.0f};
  const auto vec_1 = core::FourVec3<float>(all_x_values, all_y_values, all_z_values);
  const auto vec_2 = core::FourVec3<float>(all_y_values, all_x_values, all_x_values);

  const auto result = vec_1 - vec_2;

  EXPECT_FLOAT_EQ(result.GetX()[0], 3.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 3.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 3.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 3.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], -3.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], -3.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], -3.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], -3.0f);

  EXPECT_FLOAT_EQ(result.GetZ()[0], -4.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[1], -4.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[2], -4.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[3], -4.0f);
}


TEST(test_four_vec_3, multiply_scalar) {
  std::array<float, 4> all_x_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_y_values{2.0f, 3.0f, 4.0f, 5.0f};
  std::array<float, 4> all_z_values{3.0f, 4.0f, 5.0f, 6.0f};
  const auto vec_1 = core::FourVec3<float>(all_x_values, all_y_values, all_z_values);

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

  EXPECT_FLOAT_EQ(result.GetZ()[0], 6.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[1], 8.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[2], 10.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[3], 12.0f);
}


TEST(test_four_vec_3, divide_scalar) {
  std::array<float, 4> all_x_values{2.0f, 4.0f, 6.0f, 8.0f};
  std::array<float, 4> all_y_values{4.0f, 6.0f, 8.0f, 10.0f};
  std::array<float, 4> all_z_values{6.0f, 8.0f, 10.0f, 12.0f};
  const auto vec_1 = core::FourVec3<float>(all_x_values, all_y_values, all_z_values);

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

  EXPECT_FLOAT_EQ(result.GetZ()[0], 3.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[1], 4.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[2], 5.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[3], 6.0f);
}


TEST(test_four_vec_3, magnitude) {
  std::array<float, 4> all_x_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_y_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_z_values{1.0f, 2.0f, 3.0f, 4.0f};
  const auto vec_1 = core::FourVec3<float>(all_x_values, all_y_values, all_z_values);

  const std::array<float, 4> magnitude = vec_1.Magnitude();
  EXPECT_FLOAT_EQ(magnitude[0], std::sqrt(3.0f));
  EXPECT_FLOAT_EQ(magnitude[1], std::sqrt(12.0f));
  EXPECT_FLOAT_EQ(magnitude[2], std::sqrt(27.0f));
  EXPECT_FLOAT_EQ(magnitude[3], std::sqrt(48.0f));
}


TEST(test_four_vec_3, sqr_magnitude) {
  std::array<float, 4> all_x_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_y_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> all_z_values{1.0f, 2.0f, 3.0f, 4.0f};
  const auto vec_1 = core::FourVec3<float>(all_x_values, all_y_values, all_z_values);

  const std::array<float, 4> sqr_magnitude = vec_1.SqrtMagnitude();
  EXPECT_FLOAT_EQ(sqr_magnitude[0], 3.0f);
  EXPECT_FLOAT_EQ(sqr_magnitude[1], 12.0f);
  EXPECT_FLOAT_EQ(sqr_magnitude[2], 27.0f);
  EXPECT_FLOAT_EQ(sqr_magnitude[3], 48.0f);
}


TEST(test_four_vec_3, normalise) {
  std::array<float, 4> all_x_values{3.0f, 0.0f, 4.0f, 0.0f};
  std::array<float, 4> all_y_values{0.0f, 1.0f, 0.0f, 1.0f};
  std::array<float, 4> all_z_values{1.0f, 2.0f, 0.0f, 1.0f};
  const auto vec_1 = core::FourVec3<float>(all_x_values, all_y_values, all_z_values);

  const auto result = vec_1.Normalise();

  EXPECT_FLOAT_EQ(vec_1.GetZ()[0], 1.0f);
  EXPECT_FLOAT_EQ(vec_1.GetZ()[1], 2.0f);
  EXPECT_FLOAT_EQ(vec_1.GetZ()[2], 0.0f);
  EXPECT_FLOAT_EQ(vec_1.GetZ()[3], 1.0f);


  EXPECT_FLOAT_EQ(result.GetX()[0], 3.0f / std::sqrt(10.0f));
  EXPECT_FLOAT_EQ(result.GetX()[1], 0.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], 1.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 0.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], 0.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], 1.0f / std::sqrt(5.0f));
  EXPECT_FLOAT_EQ(result.GetY()[2], 0.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], 1 / std::sqrt(2.0f));

  EXPECT_FLOAT_EQ(result.GetZ()[0], 1 / std::sqrt(10.0f));
  EXPECT_FLOAT_EQ(result.GetZ()[1], 2.0f / std::sqrt(5.0f));
  EXPECT_FLOAT_EQ(result.GetZ()[2], 0.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[3], 1.0f / std::sqrt(2.0f));
}


TEST(test_four_vec_3, cross_product) {
  // Initialize values for two sets of 3D vectors
  std::array<float, 4> x1_values{1.0f, 2.0f, 3.0f, 4.0f};
  std::array<float, 4> y1_values{0.0f, 1.0f, 0.0f, 1.0f};
  std::array<float, 4> z1_values{0.0f, 0.0f, 1.0f, 0.0f};

  std::array<float, 4> x2_values{0.0f, 1.0f, 0.0f, 1.0f};
  std::array<float, 4> y2_values{1.0f, 0.0f, 1.0f, 0.0f};
  std::array<float, 4> z2_values{0.0f, 0.0f, 1.0f, 1.0f};

  // Create two FourVec3 objects with the initialized values
  auto vec_1 = core::FourVec3<float>(x1_values, y1_values, z1_values);
  auto vec_2 = core::FourVec3<float>(x2_values, y2_values, z2_values);

  // Compute the cross product
  const auto result = core::FourVec3<float>::Cross(vec_1, vec_2);

  EXPECT_FLOAT_EQ(result.GetX()[0], 0.0f);
  EXPECT_FLOAT_EQ(result.GetX()[1], 0.0f);
  EXPECT_FLOAT_EQ(result.GetX()[2], -1.0f);
  EXPECT_FLOAT_EQ(result.GetX()[3], 1.0f);

  EXPECT_FLOAT_EQ(result.GetY()[0], 0.0f);
  EXPECT_FLOAT_EQ(result.GetY()[1], 0.0f);
  EXPECT_FLOAT_EQ(result.GetY()[2], -3.0f);
  EXPECT_FLOAT_EQ(result.GetY()[3], -4.0f);

  EXPECT_FLOAT_EQ(result.GetZ()[0], 1.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[1], -1.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[2], 3.0f);
  EXPECT_FLOAT_EQ(result.GetZ()[3], -1.0f);
}



