//
// Created by Mat on 07.10.2024.
//

#include <gtest/gtest.h>
#include "Matrix3.h"


TEST(test_matrix_3, addition_with_int) {
    const auto value_1 = core::Matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);
    const auto value_2 = core::Matrix3<int>(0,0,0,1,2,8,0,7,14);

    //result and expectations
    const auto result = value_1 + value_2;
    const auto expected = core::Matrix3<int>(15,0,24,3,5,12,8,37,104);

    const auto actual = result - expected;

    EXPECT_EQ(actual.GetX(), 0);
    EXPECT_EQ(actual.GetY(), 0);
    EXPECT_EQ(actual.GetZ(), 0);

    EXPECT_EQ(actual.GetXPrime(), 0);
    EXPECT_EQ(actual.GetYPrime(), 0);
    EXPECT_EQ(actual.GetZPrime(), 0);

    EXPECT_EQ(actual.GetXSecond(), 0);
    EXPECT_EQ(actual.GetYSecond(), 0);
    EXPECT_EQ(actual.GetZSecond(), 0);
}


TEST(test_matrix_3, addition_with_float) {
    const auto value_1 = core::Matrix3<float>(15.0f, 0.5f, 24.4f, 2.0f, 0.0f, 1.0f, 2.7f, 8.6f, 37.2f);
    const auto value_2 = core::Matrix3<float>(8.0f, 7.4f, 5.6f, 6.8f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f);

    //result + expectations
    const auto result = value_1 + value_2;
    const auto expected = core::Matrix3<float>(23.0f, 7.9f, 30.0f, 8.8f, 7.2f, 9.2f, 2.7f, 8.6f, 37.2f);

    const auto actual = result - expected;

    EXPECT_FLOAT_EQ(actual.GetX(), 0);
    EXPECT_FLOAT_EQ(actual.GetY(), 0);
    EXPECT_FLOAT_EQ(actual.GetZ(), 0);

    EXPECT_FLOAT_EQ(actual.GetXPrime(), 0);
    EXPECT_FLOAT_EQ(actual.GetYPrime(), 0);
    EXPECT_FLOAT_EQ(actual.GetZPrime(), 0);

    EXPECT_FLOAT_EQ(actual.GetXSecond(), 0);
    EXPECT_FLOAT_EQ(actual.GetYSecond(), 0);
    EXPECT_FLOAT_EQ(actual.GetZSecond(), 0);
}


TEST(test_matrix_3, sub_with_int) {
    const auto value_1 = core::Matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);
    const auto value_2 = core::Matrix3<int>(0, 0, 0, 1, 2, 8, 0, 7, 14);

    //result and expectations
    const auto result = value_1 - value_2;

    EXPECT_EQ(result.GetX(), 15);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.GetZ(), 24);

    EXPECT_EQ(result.GetXPrime(), 1);
    EXPECT_EQ(result.GetYPrime(), 1);
    EXPECT_EQ(result.GetZPrime(), -4);

    EXPECT_EQ(result.GetXSecond(), 8);
    EXPECT_EQ(result.GetYSecond(), 23);
    EXPECT_EQ(result.GetZSecond(), 76);
}


TEST(test_matrix_3, sub_with_float) {
    const auto value_1 = core::Matrix3<float>(15.0f, 0.5f, 24.4f, 2.0f, 0.0f, 1.0f, 2.7f, 8.6f, 37.2f);
    const auto value_2 = core::Matrix3<float>(8.0f, 7.4f, 5.6f, 6.8f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f);

    //result + expectations
    const auto result = value_1 - value_2;

    EXPECT_FLOAT_EQ(result.GetX(), 7.0f);
    EXPECT_FLOAT_EQ(result.GetY(), -6.9f);
    EXPECT_FLOAT_EQ(result.GetZ(), 18.8f);

    EXPECT_FLOAT_EQ(result.GetXPrime(), -4.8f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), -7.2f);
    EXPECT_FLOAT_EQ(result.GetZPrime(), -7.2f);

    EXPECT_FLOAT_EQ(result.GetXSecond(), 2.7f);
    EXPECT_FLOAT_EQ(result.GetYSecond(), 8.6f);
    EXPECT_FLOAT_EQ(result.GetZSecond(), 37.2f);
}


TEST(test_matrix_3, gets) {
    const auto value_1 = core::Matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);

    EXPECT_EQ(value_1.GetX(), 15);
    EXPECT_EQ(value_1.GetY(), 0);
    EXPECT_EQ(value_1.GetZ(), 24);

    EXPECT_EQ(value_1.GetXPrime(), 2);
    EXPECT_EQ(value_1.GetYPrime(), 3);
    EXPECT_EQ(value_1.GetZPrime(), 4);

    EXPECT_EQ(value_1.GetXSecond(), 8);
    EXPECT_EQ(value_1.GetYSecond(), 30);
    EXPECT_EQ(value_1.GetZSecond(), 90);
}


TEST(test_matrix_3, mult_with_int) {
    const auto value_1 = core::Matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);
    const auto value_2 = core::Matrix3<int>(8, 7, 5, 6, 3, 2, 8, 0, 7);

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_EQ(result.GetX(), 174);
    EXPECT_EQ(result.GetY(), 171);
    EXPECT_EQ(result.GetZ(), 670);

    EXPECT_EQ(result.GetXPrime(), 112);
    EXPECT_EQ(result.GetYPrime(), 69);
    EXPECT_EQ(result.GetZPrime(), 336);

    EXPECT_EQ(result.GetXSecond(), 176);
    EXPECT_EQ(result.GetYSecond(), 210);
    EXPECT_EQ(result.GetZSecond(), 822);
}


TEST(test_matrix_3, mult_with_float) {
    const auto value_1 = core::Matrix3<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f);
    const auto value_2 = core::Matrix3<float>(8.9f, 7.0f, 5.0f, 6.5f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f);

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_FLOAT_EQ(result.GetX(), 155.3f);
    EXPECT_FLOAT_EQ(result.GetY(), 41.5f);
    EXPECT_FLOAT_EQ(result.GetZ(), 261.94f);

    EXPECT_FLOAT_EQ(result.GetXPrime(), 122.98f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), 50.94f);
    EXPECT_FLOAT_EQ(result.GetZPrime(), 230.42f);

    EXPECT_FLOAT_EQ(result.GetXSecond(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetYSecond(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetZSecond(), 0.0f);
}


TEST(test_matrix_3, mult_with_int_scalar) {
    const auto value_1 = core::Matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);
    constexpr int value_2 = 2;

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_EQ(result.GetX(), 30);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.GetZ(), 48);

    EXPECT_EQ(result.GetXPrime(), 4);
    EXPECT_EQ(result.GetYPrime(), 6);
    EXPECT_EQ(result.GetZPrime(), 8);

    EXPECT_EQ(result.GetXSecond(), 16);
    EXPECT_EQ(result.GetYSecond(), 60);
    EXPECT_EQ(result.GetZSecond(), 180);
}


TEST(test_matrix_3, mult_with_float_scalar) {
    const auto value_1 = core::Matrix3<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f);
    constexpr float value_2 = 2.5f;

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_FLOAT_EQ(result.GetX(), 37.5f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), 61.5f);

    EXPECT_FLOAT_EQ(result.GetXPrime(), 6.0f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), 10.0f);
    EXPECT_FLOAT_EQ(result.GetZPrime(), 0.0f);

    EXPECT_FLOAT_EQ(result.GetXSecond(), 2.5f);
    EXPECT_FLOAT_EQ(result.GetYSecond(), 6.75f);
    EXPECT_FLOAT_EQ(result.GetZSecond(), 21.5f);
}


TEST(test_matrix_3, determinant) {
    const auto value_1 = core::Matrix3<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f);

    //result + expectations
    const auto result_1 = value_1.determinant();


    EXPECT_FLOAT_EQ(result_1, 577.008f);

    const auto value_2 = core::Matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);

    //result + expectations
    const auto result_2 = value_2.determinant(); //suppose to be 30


    EXPECT_EQ(result_2, 3114);
}