//
// Created by Mat on 07.10.2024.
//

#include <gtest/gtest.h>
#include "Matrix4.h"


TEST(test_matrix_4, addition_with_int) {
    const auto value_1 = core::Matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);
    const auto value_2 = core::Matrix4<int>(0,0,0,1,2,8,0,7,14, 5, 8, 6, 3, 7, 5, 4);

    //result and expectations
    const auto result = value_1 + value_2;
    const auto expected = core::Matrix4<int>(15,0,24,3,5,12,8,37,104, 55, 16, 6, 8, 13, 12, 6);

    const auto actual = result - expected;


    EXPECT_EQ(actual.GetX(), 0);
    EXPECT_EQ(actual.GetY(), 0);
    EXPECT_EQ(actual.GetZ(), 0);
    EXPECT_EQ(actual.GetW(), 0);

    EXPECT_EQ(actual.GetXPrime(), 0);
    EXPECT_EQ(actual.GetYPrime(), 0);
    EXPECT_EQ(actual.GetZPrime(), 0);
    EXPECT_EQ(actual.GetWPrime(), 0);

    EXPECT_EQ(actual.GetXSecond(), 0);
    EXPECT_EQ(actual.GetYSecond(), 0);
    EXPECT_EQ(actual.GetZSecond(), 0);
    EXPECT_EQ(actual.GetWSecond(), 0);

    EXPECT_EQ(actual.GetXThird(), 0);
    EXPECT_EQ(actual.GetYThird(), 0);
    EXPECT_EQ(actual.GetZThird(), 0);
    EXPECT_EQ(actual.GetWThird(), 0);
}


TEST(test_matrix_4, addition_with_float) {
    const auto value_1 = core::Matrix4<float>(15.0f, 0.5f, 24.4f, 2.0f, 0.0f, 1.0f, 2.7f, 8.6f, 37.2f, 4.5f, 8.5f, 7.3f, 7.9f, 7.9f, 0.9f, 8.9f);
    const auto value_2 = core::Matrix4<float>(8.0f, 7.4f, 5.6f, 6.8f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f, 2.0f, 5.0f, 7.3f, 7.9f, 8.6f, 7.9f, 4.0f);

    //result + expectations
    const auto result = value_1 + value_2;
    const auto expected = core::Matrix4<float>(23.0f, 7.9f, 30.0f, 8.8f, 7.2f, 9.2f, 2.7f, 8.6f, 37.2f, 6.5f, 13.5f, 14.6f, 15.8f, 16.5f, 8.8f, 12.9f);

    const auto actual = result - expected;

    EXPECT_FLOAT_EQ(actual.GetX(), 0);
    EXPECT_FLOAT_EQ(actual.GetY(), 0);
    EXPECT_FLOAT_EQ(actual.GetZ(), 0);
    EXPECT_FLOAT_EQ(actual.GetW(), 0);

    EXPECT_FLOAT_EQ(actual.GetXPrime(), 0);
    EXPECT_FLOAT_EQ(actual.GetYPrime(), 0);
    EXPECT_FLOAT_EQ(actual.GetZPrime(), 0);
    EXPECT_FLOAT_EQ(actual.GetWPrime(), 0);

    EXPECT_FLOAT_EQ(actual.GetXSecond(), 0);
    EXPECT_FLOAT_EQ(actual.GetYSecond(), 0);
    EXPECT_FLOAT_EQ(actual.GetZSecond(), 0);
    EXPECT_FLOAT_EQ(actual.GetWSecond(), 0);

    EXPECT_FLOAT_EQ(actual.GetXThird(), 0);
    EXPECT_FLOAT_EQ(actual.GetYThird(), 0);
    EXPECT_FLOAT_EQ(actual.GetZThird(), 0);
    EXPECT_FLOAT_EQ(actual.GetWThird(), 0);
}


TEST(test_matrix_4, sub_with_int) {
    const auto value_1 = core::Matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);
    const auto value_2 = core::Matrix4<int>(0, 0, 0, 1, 2, 8, 0, 7, 14, 5, 8, 6, 3, 7, 5, 4);

    //result and expectations
    const auto result = value_1 - value_2;

    EXPECT_EQ(result.GetX(), 15);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.GetZ(), 24);
    EXPECT_EQ(result.GetW(), 1);

    EXPECT_EQ(result.GetXPrime(), 1);
    EXPECT_EQ(result.GetYPrime(), -4);
    EXPECT_EQ(result.GetZPrime(), 8);
    EXPECT_EQ(result.GetWPrime(), 23);

    EXPECT_EQ(result.GetXSecond(), 76);
    EXPECT_EQ(result.GetYSecond(), 45);
    EXPECT_EQ(result.GetZSecond(), 0);
    EXPECT_EQ(result.GetWSecond(), -6);

    EXPECT_EQ(result.GetXThird(), 2);
    EXPECT_EQ(result.GetYThird(), -1);
    EXPECT_EQ(result.GetZThird(), 2);
    EXPECT_EQ(result.GetWThird(), -2);
}


TEST(test_matrix_4, sub_with_float) {
    const auto value_1 = core::Matrix4<float>(15.0f, 0.5f, 24.4f, 2.0f, 0.0f, 1.0f, 2.7f, 8.6f, 37.2f, 8.0f, 7.3f, 7.9f, 7.5f, 0.9f, 8.9f, 7.5f);
    const auto value_2 = core::Matrix4<float>(8.0f, 7.4f, 5.6f, 6.8f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f, 4.5f, 8.6f, 7.9f, 8.5f, 7.9f, 4.5f, 4.6f);

    //result + expectations
    const auto result = value_1 - value_2;

    EXPECT_FLOAT_EQ(result.GetX(), 7.0f);
    EXPECT_FLOAT_EQ(result.GetY(), -6.9f);
    EXPECT_FLOAT_EQ(result.GetZ(), 18.8f);
    EXPECT_FLOAT_EQ(result.GetW(), -4.8f);

    EXPECT_FLOAT_EQ(result.GetXPrime(), -7.2f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), -7.2f);
    EXPECT_FLOAT_EQ(result.GetZPrime(), 2.7f);
    EXPECT_FLOAT_EQ(result.GetWPrime(), 8.6f);

    EXPECT_FLOAT_EQ(result.GetXSecond(), 37.2f);
    EXPECT_FLOAT_EQ(result.GetYSecond(), 3.5f);
    EXPECT_FLOAT_EQ(result.GetZSecond(), -1.3f);
    EXPECT_FLOAT_EQ(result.GetWSecond(), 0.0f);

    EXPECT_FLOAT_EQ(result.GetXThird(), -1.0f);
    EXPECT_FLOAT_EQ(result.GetYThird(), -7.0f);
    EXPECT_FLOAT_EQ(result.GetZThird(), 4.4f);
    EXPECT_FLOAT_EQ(result.GetWThird(), 2.9f);
}


TEST(test_matrix_4, gets) {
    const auto value_1 = core::Matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);

    EXPECT_EQ(value_1.GetX(), 15);
    EXPECT_EQ(value_1.GetY(), 0);
    EXPECT_EQ(value_1.GetZ(), 24);
    EXPECT_EQ(value_1.GetW(), 2);

    EXPECT_EQ(value_1.GetXPrime(), 3);
    EXPECT_EQ(value_1.GetYPrime(), 4);
    EXPECT_EQ(value_1.GetZPrime(), 8);
    EXPECT_EQ(value_1.GetWPrime(), 30);

    EXPECT_EQ(value_1.GetXSecond(), 90);
    EXPECT_EQ(value_1.GetYSecond(), 50);
    EXPECT_EQ(value_1.GetZSecond(), 8);
    EXPECT_EQ(value_1.GetWSecond(), 0);

    EXPECT_EQ(value_1.GetXThird(), 5);
    EXPECT_EQ(value_1.GetYThird(), 6);
    EXPECT_EQ(value_1.GetZThird(), 7);
    EXPECT_EQ(value_1.GetWThird(), 2);
}


TEST(test_matrix_4, mult_with_int) {
    const auto value_1 = core::Matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);
    const auto value_2 = core::Matrix4<int>(8, 7, 5, 6, 3, 2, 8, 0, 7, 6, 4, 0, 0, 5, 0, 4);

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_EQ(result.GetX(), 621);
    EXPECT_EQ(result.GetY(), 314);
    EXPECT_EQ(result.GetZ(), 330);
    EXPECT_EQ(result.GetW(), 238);

    EXPECT_EQ(result.GetXPrime(), 771);
    EXPECT_EQ(result.GetYPrime(), 408);
    EXPECT_EQ(result.GetZPrime(), 152);
    EXPECT_EQ(result.GetWPrime(), 66);

    EXPECT_EQ(result.GetXSecond(), 483);
    EXPECT_EQ(result.GetYSecond(), 224);
    EXPECT_EQ(result.GetZSecond(), 248);
    EXPECT_EQ(result.GetWSecond(), 194);

    EXPECT_EQ(result.GetXThird(), 35);
    EXPECT_EQ(result.GetYThird(), 44);
    EXPECT_EQ(result.GetZThird(), 68);
    EXPECT_EQ(result.GetWThird(), 158);
}


TEST(test_matrix_4, mult_with_float) {
    const auto value_1 = core::Matrix4<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f, 8.6f, 7.3f, 7.9f, 7.5f, 0.9f, 8.9f, 7.5f);
    const auto value_2 = core::Matrix4<float>(8.9f, 7.0f, 5.0f, 6.5f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f, 7.4f, 8.6f, 7.9f, 8.5f, 7.9f, 4.5f, 4.6f);

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_FLOAT_EQ(result.GetX(), 253.25f);
    EXPECT_FLOAT_EQ(result.GetY(), 48.85f);
    EXPECT_FLOAT_EQ(result.GetZ(), 320.29f);
    EXPECT_FLOAT_EQ(result.GetW(), 128.51f);

    EXPECT_FLOAT_EQ(result.GetXPrime(), 140.8f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetZPrime(), 185.32f);
    EXPECT_FLOAT_EQ(result.GetWPrime(), 39.42f);

    EXPECT_FLOAT_EQ(result.GetXSecond(), 162.81f);
    EXPECT_FLOAT_EQ(result.GetYSecond(), 81.07f);
    EXPECT_FLOAT_EQ(result.GetZSecond(), 140.49f);
    EXPECT_FLOAT_EQ(result.GetWSecond(), 147.17f);

    EXPECT_FLOAT_EQ(result.GetXThird(), 232.3f);
    EXPECT_FLOAT_EQ(result.GetYThird(), 42.84f);
    EXPECT_FLOAT_EQ(result.GetZThird(), 290.79f);
    EXPECT_FLOAT_EQ(result.GetWThird(), 111.78f);
}


TEST(test_matrix_4, mult_with_int_scalar) {
    const auto value_1 = core::Matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);
    constexpr int value_2 = 2;

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_EQ(result.GetX(), 30);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.GetZ(), 48);
    EXPECT_EQ(result.GetW(), 4);

    EXPECT_EQ(result.GetXPrime(), 6);
    EXPECT_EQ(result.GetYPrime(), 8);
    EXPECT_EQ(result.GetZPrime(), 16);
    EXPECT_EQ(result.GetWPrime(), 60);

    EXPECT_EQ(result.GetXSecond(), 180);
    EXPECT_EQ(result.GetYSecond(), 100);
    EXPECT_EQ(result.GetZSecond(), 16);
    EXPECT_EQ(result.GetWSecond(), 0);

    EXPECT_EQ(result.GetXThird(), 10);
    EXPECT_EQ(result.GetYThird(), 12);
    EXPECT_EQ(result.GetZThird(), 14);
    EXPECT_EQ(result.GetWThird(), 4);
}


TEST(test_matrix_4, mult_with_float_scalar) {
    const auto value_1 = core::Matrix4<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f, 4.5f, 7.3f, 7.9f, 7.5f, 0.9f, 8.9f, 7.5f);
    constexpr float value_2 = 2.5f;

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_FLOAT_EQ(result.GetX(), 37.5f);
    EXPECT_FLOAT_EQ(result.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), 61.5f);
    EXPECT_FLOAT_EQ(result.GetW(), 6.0f);

    EXPECT_FLOAT_EQ(result.GetXPrime(), 10.0f);
    EXPECT_FLOAT_EQ(result.GetYPrime(), 0.0f);
    EXPECT_FLOAT_EQ(result.GetZPrime(), 2.5f);
    EXPECT_FLOAT_EQ(result.GetWPrime(), 6.75f);

    EXPECT_FLOAT_EQ(result.GetXSecond(), 21.5f);
    EXPECT_FLOAT_EQ(result.GetYSecond(), 11.25f);
    EXPECT_FLOAT_EQ(result.GetZSecond(), 18.25f);
    EXPECT_FLOAT_EQ(result.GetWSecond(), 19.75f);

    EXPECT_FLOAT_EQ(result.GetXThird(), 18.75f);
    EXPECT_FLOAT_EQ(result.GetYThird(), 2.25f);
    EXPECT_FLOAT_EQ(result.GetZThird(), 22.25f);
    EXPECT_FLOAT_EQ(result.GetWThird(), 18.75f);
}


TEST(test_matrix_4, determinant) {
    const auto value_1 = core::Matrix4<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f, 4.5f, 7.3f, 7.9f, 7.5f, 0.9f, 8.9f, 7.5f);

    //result + expectations
    const auto result_1 = value_1.determinant();


    EXPECT_FLOAT_EQ(result_1, 1591.1478f);

    const auto value_2 = core::Matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);

    //result + expectations
    const auto result_2 = value_2.determinant();


    EXPECT_EQ(result_2, 321848);
}
