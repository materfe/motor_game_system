//
// Created by Mat on 07.10.2024.
//

#include <gtest/gtest.h>
#include "matrix2.h"



TEST(test_matrix_2, addition_with_int) {
    const auto value_1 = core::matrix2<int>(15, 0, 24, 2);
    const auto value_2 = core::matrix2<int>(8, 7, 5, 6);

    //result and expectations
    const auto result = value_1 + value_2; //suppose to be : a = 23, b = 7, c = 29, d = 8
    const auto expected = core::matrix2<int>(23, 7, 24, 7);

    const auto actual = result - expected;

    EXPECT_EQ(actual.GetFirstColumn().x_, 0);
    EXPECT_EQ(actual.GetFirstColumn().y_, 0);
    EXPECT_EQ(actual.GetSecondColumn().x_, 5);
    EXPECT_EQ(actual.GetSecondColumn().y_, 1);
}


TEST(test_matrix_2, addition_with_float) {
    const auto value_1 = core::matrix2<float>(15.0f, 0.5f, 24.4f, 2.0f);
    const auto value_2 = core::matrix2<float>(8.0f, 7.4f, 5.6f, 6.8f);

    //result + expectations
    const auto result = value_1 + value_2; //suppose to be : a = 23, b = 7.9, c = 30, d = 8.8
    const auto expected = core::matrix2<float>(21.5, 7.9, 25.0, 7.8f);

    const auto actual = result - expected;

    EXPECT_FLOAT_EQ(actual.GetFirstColumn().x_, 1.5);
    EXPECT_FLOAT_EQ(actual.GetFirstColumn().y_, 0);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().x_, 5.0);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().y_, 1.0);
}


TEST(test_matrix_2, sub_with_int) {
    const auto value_1 = core::matrix2<int>(15, 0, 24, 2);
    const auto value_2 = core::matrix2<int>(8, 7, 5, 6);

    //result and expectations
    const auto result = value_1 - value_2; //suppose to be : a = 7, b = -7, c = 19, d = -4

    EXPECT_EQ(result.GetFirstColumn().x_, 7);
    EXPECT_EQ(result.GetFirstColumn().y_, -7);
    EXPECT_EQ(result.GetSecondColumn().x_, 19);
    EXPECT_EQ(result.GetSecondColumn().y_, -4);
}


TEST(test_matrix_2, sub_with_float) {
    const auto value_1 = core::matrix2<float>(15.0f, 0.5f, 24.4f, 2.0f);
    const auto value_2 = core::matrix2<float>(8.0f, 7.4f, 5.6f, 6.8f);

    //result + expectations
    const auto result = value_1 - value_2; //suppose to be : a = 7, b = -6.9, c = 18.8, d = -4.8

    EXPECT_FLOAT_EQ(result.GetFirstColumn().x_, 7.0f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().y_, -6.9f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().x_, 18.8f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().y_, -4.8f);
}


TEST(test_matrix_2, gets) {
    const auto value_1 = core::matrix2<int>(15, 0, 24, 2);

    EXPECT_EQ(value_1.GetFirstColumn().x_, 15);
    EXPECT_EQ(value_1.GetFirstColumn().y_, 0);
    EXPECT_EQ(value_1.GetSecondColumn().x_, 24);
    EXPECT_EQ(value_1.GetSecondColumn().y_, 2);
}


TEST(test_matrix_2, mult_with_int) {
    const auto value_1 = core::matrix2<int>(15, 0, 24, 2);
    const auto value_2 = core::matrix2<int>(8, 7, 5, 6);

    //result + expectations
    const auto result = value_1 * value_2; //suppose to be : a = 288, b = 14, c = 219, d = 12


    EXPECT_EQ(result.GetFirstColumn().x_, 288);
    EXPECT_EQ(result.GetFirstColumn().y_, 14);
    EXPECT_EQ(result.GetSecondColumn().x_, 219);
    EXPECT_EQ(result.GetSecondColumn().y_, 12);
}


TEST(test_matrix_2, mult_with_float) {
    const auto value_1 = core::matrix2<float>(15.0f, 0.0f, 24.6f, 2.4f);
    const auto value_2 = core::matrix2<float>(8.9f, 7.0f, 5.0f, 6.5f);

    //result + expectations
    const auto result = value_1 * value_2; //suppose to be : a = 305.7, b = 16.8, c = 234.9, d = 15.6


    EXPECT_FLOAT_EQ(result.GetFirstColumn().x_, 305.7f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().y_, 16.8f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().x_, 234.9f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().y_, 15.6f);
}


TEST(test_matrix_2, mult_with_int_scalar) {
    const auto value_1 = core::matrix2<int>(15, 0, 24, 2);
    constexpr int value_2 = 5;

    //result + expectations
    const auto result = value_1 * value_2; //suppose to be : a = 75, b = 0, c = 120, d = 10


    EXPECT_EQ(result.GetFirstColumn().x_, 75);
    EXPECT_EQ(result.GetFirstColumn().y_, 0);
    EXPECT_EQ(result.GetSecondColumn().x_, 120);
    EXPECT_EQ(result.GetSecondColumn().y_, 10);
}


TEST(test_matrix_2, mult_with_float_scalar) {
    const auto value_1 = core::matrix2<float>(15.0f, 0.0f, 24.6f, 2.4f);
    constexpr float value_2 = 6.2f;

    //result + expectations
    const auto result = value_1 * value_2; //suppose to be : a = 93, b = 0, c = 152.52, d = 14.88


    EXPECT_FLOAT_EQ(result.GetFirstColumn().x_, 93.0f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().y_, 0.0f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().x_, 152.52f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().y_, 14.88f);
}


TEST(test_matrix_2, determinant) {
    const auto value_1 = core::matrix2<float>(15.0f, 0.0f, 24.6f, 2.4f);

    //result + expectations
    const auto result_1 = value_1.Determinant(); //suppose to be 36


    EXPECT_FLOAT_EQ(result_1, 36.0f);

    const auto value_2 = core::matrix2<int>(15, 0, 24, 2);

    //result + expectations
    const auto result_2 = value_2.Determinant(); //suppose to be 30


    EXPECT_EQ(result_2, 30);
}


TEST(test_matrix_2, inverse) {
    const auto value_1 = core::matrix2<int>(15, 0, 24, 2);

    const auto result = value_1.Inverse();

    EXPECT_EQ(result.GetFirstColumn().x_, 0);
    EXPECT_EQ(result.GetFirstColumn().y_, 0);
    EXPECT_EQ(result.GetSecondColumn().x_, 0);
    EXPECT_EQ(result.GetSecondColumn().y_, 0);
}


TEST(test_matrix_2, identity) {
    const auto value_1 = core::matrix2<int>::Identity();

    EXPECT_EQ(value_1.GetFirstColumn().x_, 1);
    EXPECT_EQ(value_1.GetFirstColumn().y_, 0);
    EXPECT_EQ(value_1.GetSecondColumn().x_, 0);
    EXPECT_EQ(value_1.GetSecondColumn().y_, 1);
}


TEST(test_matrix_2, constructor) {
    constexpr int x = 12, y = 13, z = 14, w = 15;

    const auto v = core::matrix2<int>{4, 5, 6, 7};
    const auto m = core::matrix2<int>{core::vec2<int>(1, 2), core::vec2<int>(2, 3)};

    //for v
    EXPECT_EQ(v.GetFirstColumn().x_, 4);
    EXPECT_EQ(v.GetFirstColumn().y_, 5);
    EXPECT_EQ(v.GetSecondColumn().x_, 6);
    EXPECT_EQ(v.GetSecondColumn().y_, 7);

    EXPECT_EQ(m.GetFirstColumn().x_, 1);
    EXPECT_EQ(m.GetFirstColumn().y_, 2);
    EXPECT_EQ(m.GetSecondColumn().x_, 2);
    EXPECT_EQ(m.GetSecondColumn().y_, 3);
}