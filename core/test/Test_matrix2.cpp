//
// Created by Mat on 07.10.2024.
//

#include <gtest/gtest.h>
#include "Matrix2.h"



TEST(test_matrix_2, addition_with_int) {
    const auto value_1 = core::Matrix2<int>(15, 0, 24, 2);
    const auto value_2 = core::Matrix2<int>(8, 7, 5, 6);

    //result and expectations
    const auto result = value_1 + value_2; //suppose to be : a = 23, b = 7, c = 29, d = 8
    const auto expected = core::Matrix2<int>(23, 7, 29, 8);

    const auto actual = result - expected;

    EXPECT_EQ(actual.GetX(), 0);
    EXPECT_EQ(actual.GetY(), 0);
    EXPECT_EQ(actual.GetXPrime(), 0);
    EXPECT_EQ(actual.GetYPrime(), 0);
}


TEST(test_matrix_2, addition_with_float) {
    const auto value_1 = core::Matrix2<float>(15.0f, 0.5f, 24.4f, 2.0f);
    const auto value_2 = core::Matrix2<float>(8.0f, 7.4f, 5.6f, 6.8f);

    //result + expectations
    const auto result = value_1 + value_2; //suppose to be : a = 23, b = 7.9, c = 30, d = 8.8
    const auto expected = core::Matrix2<float>(23, 7.9, 30, 8.8);

    const auto actual = result - expected;

    EXPECT_FLOAT_EQ(actual.GetX(), 0);
    EXPECT_FLOAT_EQ(actual.GetY(), 0);
    EXPECT_FLOAT_EQ(actual.GetXPrime(), 0);
    EXPECT_FLOAT_EQ(actual.GetYPrime(), 0);
}


TEST(test_matrix_2, sub_with_int) {
    const auto value_1 = core::Matrix2<int>(15, 0, 24, 2);
    const auto value_2 = core::Matrix2<int>(8, 7, 5, 6);

    //result and expectations
    const auto result = value_1 - value_2; //suppose to be : a = 7, b = -7, c = 19, d = -4

    EXPECT_EQ(result.GetX(), 7);
    EXPECT_EQ(result.GetY(), -7);
    EXPECT_EQ(result.GetXPrime(), 19);
    EXPECT_EQ(result.GetYPrime(), -4);
}


TEST(test_matrix_2, sub_with_float) {
    const auto value_1 = core::Matrix2<float>(15.0f, 0.5f, 24.4f, 2.0f);
    const auto value_2 = core::Matrix2<float>(8.0f, 7.4f, 5.6f, 6.8f);

    //result + expectations
    const auto result = value_1 - value_2; //suppose to be : a = 7, b = -6.9, c = 18.8, d = -4.8

    EXPECT_FLOAT_EQ(result.GetX(), 7.0f);
    EXPECT_FLOAT_EQ(result.GetY(), -6.9f);
    EXPECT_FLOAT_EQ(result.GetXPrime(), 18.8f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), -4.8f);
}

TEST(test_matrix_2, gets) {
    const auto value_1 = core::Matrix2<int>(15, 0, 24, 2);

    EXPECT_EQ(value_1.GetX(), 15);
    EXPECT_EQ(value_1.GetY(), 0);
    EXPECT_EQ(value_1.GetXPrime(), 24);
    EXPECT_EQ(value_1.GetYPrime(), 2);
}


TEST(test_matrix_2, mult_with_int) {
    const auto value_1 = core::Matrix2<int>(15, 0, 24, 2);
    const auto value_2 = core::Matrix2<int>(8, 7, 5, 6);

    //result + expectations
    const auto result = value_1 * value_2; //suppose to be : a = 288, b = 14, c = 219, d = 12


    EXPECT_EQ(result.GetX(), 288);
    EXPECT_EQ(result.GetY(), 14);
    EXPECT_EQ(result.GetXPrime(), 219);
    EXPECT_EQ(result.GetYPrime(), 12);
}


TEST(test_matrix_2, mult_with_float) {
    const auto value_1 = core::Matrix2<float>(15.0f, 0.0f, 24.6f, 2.4f);
    const auto value_2 = core::Matrix2<float>(8.9f, 7.0f, 5.0f, 6.5f);

    //result + expectations
    const auto result = value_1 * value_2; //suppose to be : a = 305.7, b = 16.8, c = 234.9, d = 15.6


    EXPECT_FLOAT_EQ(result.GetX(), 305.7f);
    EXPECT_FLOAT_EQ(result.GetY(), 16.8f);
    EXPECT_FLOAT_EQ(result.GetXPrime(), 234.9f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), 15.6f);
}

TEST(test_matrix_2, mult_with_int_scalar) {
    const auto value_1 = core::Matrix2<int>(15, 0, 24, 2);
    constexpr int value_2 = 5;

    //result + expectations
    const auto result = value_1 * value_2; //suppose to be : a = 75, b = 0, c = 120, d = 10


    EXPECT_EQ(result.GetX(), 75);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.GetXPrime(), 120);
    EXPECT_EQ(result.GetYPrime(), 10);
}


TEST(test_matrix_2, mult_with_float_scalar) {
    const auto value_1 = core::Matrix2<float>(15.0f, 0.0f, 24.6f, 2.4f);
    constexpr float value_2 = 6.2f;

    //result + expectations
    const auto result = value_1 * value_2; //suppose to be : a = 93, b = 0, c = 152.52, d = 14.88


    EXPECT_FLOAT_EQ(result.GetX(), 93.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetXPrime(), 152.52f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), 14.88f);
}


TEST(test_matrix_2, determinant) {
    const auto value_1 = core::Matrix2<float>(15.0f, 0.0f, 24.6f, 2.4f);

    //result + expectations
    const auto result_1 = value_1.determinant(); //suppose to be 36


    EXPECT_FLOAT_EQ(result_1, 36.0f);

    const auto value_2 = core::Matrix2<int>(15, 0, 24, 2);

    //result + expectations
    const auto result_2 = value_2.determinant(); //suppose to be 30


    EXPECT_EQ(result_2, 30);
}