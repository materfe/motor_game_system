//
// Created by Mat on 07.10.2024.
//

#include <gtest/gtest.h>
#include <iostream>
#include "matrix3.h"


TEST(test_matrix_3, addition_with_int) {
    const auto value_1 = core::matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 15);
    const auto value_2 = core::matrix3<int>(0,0,0,1,2,8,0,7, 2);

    //result and expectations
    const auto result = value_1 + value_2;
    const auto expected = core::matrix3<int>(10,0,24,3,5,12,0,37, 10);

    const auto actual = result - expected;

    EXPECT_EQ(actual.GetFirstColumn().x, 5);
    EXPECT_EQ(actual.GetFirstColumn().y, 0);
    EXPECT_EQ(actual.GetFirstColumn().z, 0);

    EXPECT_EQ(actual.GetSecondColumn().x, 0);
    EXPECT_EQ(actual.GetSecondColumn().y, 0);
    EXPECT_EQ(actual.GetSecondColumn().z, 0);

    EXPECT_EQ(actual.GetThirdColumn().x, 8);
    EXPECT_EQ(actual.GetThirdColumn().y, 0);
    EXPECT_EQ(actual.GetThirdColumn().z, 7);
}


TEST(test_matrix_3, addition_with_float) {
    const auto value_1 = core::matrix3<float>(15.0f, 0.5f, 24.4f, 2.0f, 0.0f, 1.0f, 2.7f, 8.6f, 0.0);
    const auto value_2 = core::matrix3<float>(8.0f, 7.4f, 5.6f, 6.8f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0);

    //result + expectations
    const auto result = value_1 + value_2;
    const auto expected = core::matrix3<float>(23.0f, 7.9f, 25.0f, 7.8f, 7.2f, 9.2f, 2.7f, 8.6f, 0.0);

    const auto actual = result - expected;

    EXPECT_FLOAT_EQ(actual.GetFirstColumn().x, 0.0);
    EXPECT_FLOAT_EQ(actual.GetFirstColumn().y, 0.0);
    EXPECT_FLOAT_EQ(actual.GetFirstColumn().z, 5.0);

    EXPECT_FLOAT_EQ(actual.GetSecondColumn().x, 1.0);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().y, 0.0);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().z, 0.0);

    EXPECT_FLOAT_EQ(actual.GetThirdColumn().x, 0.0);
    EXPECT_FLOAT_EQ(actual.GetThirdColumn().y, 0.0);
    EXPECT_FLOAT_EQ(actual.GetThirdColumn().z, 0.0);
}


TEST(test_matrix_3, sub_with_int) {
    const auto value_1 = core::matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 40);
    const auto value_2 = core::matrix3<int>(0, 0, 0, 1, 2, 8, 0, 7, 1);

    //result and expectations
    const auto actual = value_1 - value_2;

    EXPECT_EQ(actual.GetFirstColumn().x, 15);
    EXPECT_EQ(actual.GetFirstColumn().y, 0);
    EXPECT_EQ(actual.GetFirstColumn().z, 24);

    EXPECT_EQ(actual.GetSecondColumn().x, 1);
    EXPECT_EQ(actual.GetSecondColumn().y, 1);
    EXPECT_EQ(actual.GetSecondColumn().z, -4);

    EXPECT_EQ(actual.GetThirdColumn().x, 8);
    EXPECT_EQ(actual.GetThirdColumn().y, 23);
    EXPECT_EQ(actual.GetThirdColumn().z, 39);
}


TEST(test_matrix_3, sub_with_float) {
    const auto value_1 = core::matrix3<float>(15.0f, 0.5f, 24.4f, 2.0f, 0.0f, 1.0f, 2.7f, 8.6f, 37.2f);
    const auto value_2 = core::matrix3<float>(8.0f, 7.4f, 5.6f, 6.8f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f);

    //result + expectations
    const auto actual = value_1 - value_2;

    EXPECT_FLOAT_EQ(actual.GetFirstColumn().x, 7.0);
    EXPECT_FLOAT_EQ(actual.GetFirstColumn().y, -6.9);
    EXPECT_FLOAT_EQ(actual.GetFirstColumn().z, 18.8);

    EXPECT_FLOAT_EQ(actual.GetSecondColumn().x, -4.8);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().y, -7.2);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().z, -7.2);

    EXPECT_FLOAT_EQ(actual.GetThirdColumn().x, 2.7);
    EXPECT_FLOAT_EQ(actual.GetThirdColumn().y, 8.6);
    EXPECT_FLOAT_EQ(actual.GetThirdColumn().z, 37.2);
}


TEST(test_matrix_3, gets) {
    const auto value_1 = core::matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);

    EXPECT_EQ(value_1.GetFirstColumn().x, 15);
    EXPECT_EQ(value_1.GetFirstColumn().y, 0);
    EXPECT_EQ(value_1.GetFirstColumn().z, 24);

    EXPECT_EQ(value_1.GetSecondColumn().x, 2);
    EXPECT_EQ(value_1.GetSecondColumn().y, 3);
    EXPECT_EQ(value_1.GetSecondColumn().z, 4);

    EXPECT_EQ(value_1.GetThirdColumn().x, 8);
    EXPECT_EQ(value_1.GetThirdColumn().y, 30);
    EXPECT_EQ(value_1.GetThirdColumn().z, 90);
}


TEST(test_matrix_3, mult_with_int) {
    const auto value_1 = core::matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);
    const auto value_2 = core::matrix3<int>(8, 7, 5, 6, 3, 2, 8, 0, 7);

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_EQ(result.GetFirstColumn().x, 174);
    EXPECT_EQ(result.GetFirstColumn().y, 171);
    EXPECT_EQ(result.GetFirstColumn().z, 670);

    EXPECT_EQ(result.GetSecondColumn().x, 112);
    EXPECT_EQ(result.GetSecondColumn().y, 69);
    EXPECT_EQ(result.GetSecondColumn().z, 336);

    EXPECT_EQ(result.GetThirdColumn().x, 176);
    EXPECT_EQ(result.GetThirdColumn().y, 210);
    EXPECT_EQ(result.GetThirdColumn().z, 822);
}


TEST(test_matrix_3, mult_with_float) {
    const auto value_1 = core::matrix3<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f);
    const auto value_2 = core::matrix3<float>(8.9f, 7.0f, 5.0f, 6.5f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f);

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_FLOAT_EQ(result.GetFirstColumn().x, 155.3f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().y, 41.5f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().z, 261.94f);

    EXPECT_FLOAT_EQ(result.GetSecondColumn().x, 122.98f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().y, 50.94f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().z, 230.42f);

    EXPECT_FLOAT_EQ(result.GetThirdColumn().x, 0.0f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().y, 0.0f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().z, 0.0f);
}


TEST(test_matrix_3, mult_with_int_scalar) {
    const auto value_1 = core::matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);
    constexpr int value_2 = 2;

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_EQ(result.GetFirstColumn().x, 30);
    EXPECT_EQ(result.GetFirstColumn().y, 0);
    EXPECT_EQ(result.GetFirstColumn().z, 48);

    EXPECT_EQ(result.GetSecondColumn().x, 4);
    EXPECT_EQ(result.GetSecondColumn().y, 6);
    EXPECT_EQ(result.GetSecondColumn().z, 8);

    EXPECT_EQ(result.GetThirdColumn().x, 16);
    EXPECT_EQ(result.GetThirdColumn().y, 60);
    EXPECT_EQ(result.GetThirdColumn().z, 180);
}


TEST(test_matrix_3, mult_with_float_scalar) {
    const auto value_1 = core::matrix3<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f);
    constexpr float value_2 = 2.5f;

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_FLOAT_EQ(result.GetFirstColumn().x, 37.5f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().y, 0.0f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().z, 61.5f);

    EXPECT_FLOAT_EQ(result.GetSecondColumn().x, 6.0f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().y, 10.0f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().z, 0.0f);

    EXPECT_FLOAT_EQ(result.GetThirdColumn().x, 2.5f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().y, 6.75f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().z, 21.5f);
}


TEST(test_matrix_3, determinant) {
    const auto value_1 = core::matrix3<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f);

    //result + expectations
    const auto result_1 = value_1.determinant();


    EXPECT_FLOAT_EQ(result_1, 577.008f);

    const auto value_2 = core::matrix3<int>(15, 0, 24, 2, 3, 4, 8, 30, 90);

    //result + expectations
    const auto result_2 = value_2.determinant(); //suppose to be 30


    EXPECT_EQ(result_2, 3114);
}


TEST(test_matrix_3, identity) {
    const auto result = core::matrix3<int>::Identity();

    EXPECT_EQ(result.GetFirstColumn().x, 1);
    EXPECT_EQ(result.GetFirstColumn().y, 0);
    EXPECT_EQ(result.GetFirstColumn().z, 0);

    EXPECT_EQ(result.GetSecondColumn().x, 0);
    EXPECT_EQ(result.GetSecondColumn().y, 1);
    EXPECT_EQ(result.GetSecondColumn().z, 0);

    EXPECT_EQ(result.GetThirdColumn().x, 0);
    EXPECT_EQ(result.GetThirdColumn().y, 0);
    EXPECT_EQ(result.GetThirdColumn().z, 1);
}


TEST(test_matrix_3, operator_) {
    const auto result = core::matrix3<int>{1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_EQ(result(0, 0), 1);
    EXPECT_EQ(result(0, 1), 2);
    EXPECT_EQ(result(0, 2), 3);

    EXPECT_EQ(result(1, 0), 4);
    EXPECT_EQ(result(1, 1), 5);
    EXPECT_EQ(result(1, 2), 6);

    EXPECT_EQ(result(2, 0), 7);
    EXPECT_EQ(result(2, 1), 8);
    EXPECT_EQ(result(2, 2), 9);
}

TEST(test_matrix_3, operator_crash) {

    const auto v = core::matrix3<int>{4, 5, 6, 7, 8, 9, 10, 11, 12};

    EXPECT_EXIT(v(4, 0), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(v(-1, 0), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(v(0, 4), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(v(0, -1), ::testing::ExitedWithCode(3), "");
}
