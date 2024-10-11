//
// Created by Mat on 07.10.2024.
//

#include <gtest/gtest.h>
#include <iostream>
#include "matrix4.h"


TEST(test_matrix_4, addition_with_int) {
    const auto value_1 = core::matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);
    const auto value_2 = core::matrix4<int>(0,0,0,1,2,8,0,7,14, 5, 8, 6, 3, 7, 5, 4);

    //result and expectations
    const auto result = value_1 + value_2;
    const auto expected = core::matrix4<int>(15,0,24,3,5,12,8,37,104, 55, 16, 6, 8, 13, 12, 6);

    const auto actual = result - expected;


    EXPECT_EQ(actual.GetFirstColumn().x, 0);
    EXPECT_EQ(actual.GetFirstColumn().y, 0);
    EXPECT_EQ(actual.GetFirstColumn().z, 0);
    EXPECT_EQ(actual.GetFirstColumn().w, 0);

    EXPECT_EQ(actual.GetSecondColumn().x, 0);
    EXPECT_EQ(actual.GetSecondColumn().y, 0);
    EXPECT_EQ(actual.GetSecondColumn().z, 0);
    EXPECT_EQ(actual.GetSecondColumn().w, 0);

    EXPECT_EQ(actual.GetThirdColumn().x, 0);
    EXPECT_EQ(actual.GetThirdColumn().y, 0);
    EXPECT_EQ(actual.GetThirdColumn().z, 0);
    EXPECT_EQ(actual.GetThirdColumn().w, 0);

    EXPECT_EQ(actual.GetFourthColumn().x, 0);
    EXPECT_EQ(actual.GetFourthColumn().y, 0);
    EXPECT_EQ(actual.GetFourthColumn().z, 0);
    EXPECT_EQ(actual.GetFourthColumn().w, 0);
}


TEST(test_matrix_4, addition_with_float) {
    const auto value_1 = core::matrix4<float>(15.0f, 0.5f, 24.4f, 2.0f, 0.0f, 1.0f, 2.7f, 8.6f, 37.2f, 4.5f, 8.5f, 7.3f, 7.9f, 7.9f, 0.9f, 8.9f);
    const auto value_2 = core::matrix4<float>(8.0f, 7.4f, 5.6f, 6.8f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f, 2.0f, 5.0f, 7.3f, 7.9f, 8.6f, 7.9f, 4.0f);

    //result + expectations
    const auto result = value_1 + value_2;
    const auto expected = core::matrix4<float>(23.0f, 7.9f, 30.0f, 8.8f, 7.2f, 9.2f, 2.7f, 8.6f, 37.2f, 6.5f, 13.5f, 14.6f, 15.8f, 16.5f, 8.8f, 12.9f);

    const auto actual = result - expected;

    EXPECT_FLOAT_EQ(actual.GetFirstColumn().x, 0);
    EXPECT_FLOAT_EQ(actual.GetFirstColumn().y, 0);
    EXPECT_FLOAT_EQ(actual.GetFirstColumn().z, 0);
    EXPECT_FLOAT_EQ(actual.GetFirstColumn().w, 0);

    EXPECT_FLOAT_EQ(actual.GetSecondColumn().x, 0);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().y, 0);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().z, 0);
    EXPECT_FLOAT_EQ(actual.GetSecondColumn().w, 0);

    EXPECT_FLOAT_EQ(actual.GetThirdColumn().x, 0);
    EXPECT_FLOAT_EQ(actual.GetThirdColumn().y, 0);
    EXPECT_FLOAT_EQ(actual.GetThirdColumn().z, 0);
    EXPECT_FLOAT_EQ(actual.GetThirdColumn().w, 0);

    EXPECT_FLOAT_EQ(actual.GetFourthColumn().x, 0);
    EXPECT_FLOAT_EQ(actual.GetFourthColumn().y, 0);
    EXPECT_FLOAT_EQ(actual.GetFourthColumn().z, 0);
    EXPECT_FLOAT_EQ(actual.GetFourthColumn().w, 0);
}


TEST(test_matrix_4, sub_with_int) {
    const auto value_1 = core::matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);
    const auto value_2 = core::matrix4<int>(0, 0, 0, 1, 2, 8, 0, 7, 14, 5, 8, 6, 3, 7, 5, 4);

    //result and expectations
    const auto result = value_1 - value_2;

    EXPECT_EQ(result.GetFirstColumn().x, 15);
    EXPECT_EQ(result.GetFirstColumn().y, 0);
    EXPECT_EQ(result.GetFirstColumn().z, 24);
    EXPECT_EQ(result.GetFirstColumn().w, 1);

    EXPECT_EQ(result.GetSecondColumn().x, 1);
    EXPECT_EQ(result.GetSecondColumn().y, -4);
    EXPECT_EQ(result.GetSecondColumn().z, 8);
    EXPECT_EQ(result.GetSecondColumn().w, 23);

    EXPECT_EQ(result.GetThirdColumn().x, 76);
    EXPECT_EQ(result.GetThirdColumn().y, 45);
    EXPECT_EQ(result.GetThirdColumn().z, 0);
    EXPECT_EQ(result.GetThirdColumn().w, -6);

    EXPECT_EQ(result.GetFourthColumn().x, 2);
    EXPECT_EQ(result.GetFourthColumn().y, -1);
    EXPECT_EQ(result.GetFourthColumn().z, 2);
    EXPECT_EQ(result.GetFourthColumn().w, -2);
}


TEST(test_matrix_4, sub_with_float) {
    const auto value_1 = core::matrix4<float>(15.0f, 0.5f, 24.4f, 2.0f, 0.0f, 1.0f, 2.7f, 8.6f, 37.2f, 8.0f, 7.3f, 7.9f, 7.5f, 0.9f, 8.9f, 7.5f);
    const auto value_2 = core::matrix4<float>(8.0f, 7.4f, 5.6f, 6.8f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f, 4.5f, 8.6f, 7.9f, 8.5f, 7.9f, 4.5f, 4.6f);

    //result + expectations
    const auto result = value_1 - value_2;

    EXPECT_FLOAT_EQ(result.GetFirstColumn().x, 7.0f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().y, -6.9f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().z, 18.8f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().w, -4.8f);

    EXPECT_FLOAT_EQ(result.GetSecondColumn().x, -7.2f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().y, -7.2f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().z, 2.7f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().w, 8.6f);

    EXPECT_FLOAT_EQ(result.GetThirdColumn().x, 37.2f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().y, 3.5f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().z, -1.3f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().w, 0.0f);

    EXPECT_FLOAT_EQ(result.GetFourthColumn().x, -1.0f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().y, -7.0f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().z, 4.4f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().w, 2.9f);
}


TEST(test_matrix_4, gets) {
    const auto value_1 = core::matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);

    EXPECT_EQ(value_1.GetFirstColumn().x, 15);
    EXPECT_EQ(value_1.GetFirstColumn().y, 0);
    EXPECT_EQ(value_1.GetFirstColumn().z, 24);
    EXPECT_EQ(value_1.GetFirstColumn().w, 2);

    EXPECT_EQ(value_1.GetSecondColumn().x, 3);
    EXPECT_EQ(value_1.GetSecondColumn().y, 4);
    EXPECT_EQ(value_1.GetSecondColumn().z, 8);
    EXPECT_EQ(value_1.GetSecondColumn().w, 30);

    EXPECT_EQ(value_1.GetThirdColumn().x, 90);
    EXPECT_EQ(value_1.GetThirdColumn().y, 50);
    EXPECT_EQ(value_1.GetThirdColumn().z, 8);
    EXPECT_EQ(value_1.GetThirdColumn().w, 0);

    EXPECT_EQ(value_1.GetFourthColumn().x, 5);
    EXPECT_EQ(value_1.GetFourthColumn().y, 6);
    EXPECT_EQ(value_1.GetFourthColumn().z, 7);
    EXPECT_EQ(value_1.GetFourthColumn().w, 2);
}


TEST(test_matrix_4, mult_with_int) {
    const auto value_1 = core::matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);
    const auto value_2 = core::matrix4<int>(8, 7, 5, 6, 3, 2, 8, 0, 7, 6, 4, 0, 0, 5, 0, 4);

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_EQ(result.GetFirstColumn().x, 621);
    EXPECT_EQ(result.GetFirstColumn().y, 314);
    EXPECT_EQ(result.GetFirstColumn().z, 330);
    EXPECT_EQ(result.GetFirstColumn().w, 238);

    EXPECT_EQ(result.GetSecondColumn().x, 771);
    EXPECT_EQ(result.GetSecondColumn().y, 408);
    EXPECT_EQ(result.GetSecondColumn().z, 152);
    EXPECT_EQ(result.GetSecondColumn().w, 66);

    EXPECT_EQ(result.GetThirdColumn().x, 483);
    EXPECT_EQ(result.GetThirdColumn().y, 224);
    EXPECT_EQ(result.GetThirdColumn().z, 248);
    EXPECT_EQ(result.GetThirdColumn().w, 194);

    EXPECT_EQ(result.GetFourthColumn().x, 35);
    EXPECT_EQ(result.GetFourthColumn().y, 44);
    EXPECT_EQ(result.GetFourthColumn().z, 68);
    EXPECT_EQ(result.GetFourthColumn().w, 158);
}


TEST(test_matrix_4, mult_with_float) {
    const auto value_1 = core::matrix4<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f, 8.6f, 7.3f, 7.9f, 7.5f, 0.9f, 8.9f, 7.5f);
    const auto value_2 = core::matrix4<float>(8.9f, 7.0f, 5.0f, 6.5f, 7.2f, 8.2f, 0.0f, 0.0f, 0.0f, 7.4f, 8.6f, 7.9f, 8.5f, 7.9f, 4.5f, 4.6f);

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_FLOAT_EQ(result.GetFirstColumn().x, 253.25f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().y, 48.85f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().z, 320.29f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().w, 128.51f);

    EXPECT_FLOAT_EQ(result.GetSecondColumn().x, 140.8f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().y, 0.0f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().z, 185.32f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().w, 39.42f);

    EXPECT_FLOAT_EQ(result.GetThirdColumn().x, 162.81f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().y, 81.07f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().z, 140.49f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().w, 147.17f);

    EXPECT_FLOAT_EQ(result.GetFourthColumn().x, 232.3f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().y, 42.84f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().z, 290.79f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().w, 111.78f);
}


TEST(test_matrix_4, mult_with_int_scalar) {
    const auto value_1 = core::matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);
    constexpr int value_2 = 2;

    //result + expectations
    const auto result = value_1 * value_2;


    EXPECT_EQ(result.GetFirstColumn().x, 30);
    EXPECT_EQ(result.GetFirstColumn().y, 0);
    EXPECT_EQ(result.GetFirstColumn().z, 48);
    EXPECT_EQ(result.GetFirstColumn().w, 4);

    EXPECT_EQ(result.GetSecondColumn().x, 6);
    EXPECT_EQ(result.GetSecondColumn().y, 8);
    EXPECT_EQ(result.GetSecondColumn().z, 16);
    EXPECT_EQ(result.GetSecondColumn().w, 60);

    EXPECT_EQ(result.GetThirdColumn().x, 180);
    EXPECT_EQ(result.GetThirdColumn().y, 100);
    EXPECT_EQ(result.GetThirdColumn().z, 16);
    EXPECT_EQ(result.GetThirdColumn().w, 0);

    EXPECT_EQ(result.GetFourthColumn().x, 10);
    EXPECT_EQ(result.GetFourthColumn().y, 12);
    EXPECT_EQ(result.GetFourthColumn().z, 14);
    EXPECT_EQ(result.GetFourthColumn().w, 4);
}


TEST(test_matrix_4, mult_with_float_scalar) {
    const auto value_1 = core::matrix4<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f, 4.5f, 7.3f, 7.9f, 7.5f, 0.9f, 8.9f, 7.5f);
    constexpr float value_2 = 2.5f;

    //result + expectations
    const auto result = value_1 * value_2;

    EXPECT_FLOAT_EQ(result.GetFirstColumn().x, 37.5f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().y, 0.0f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().z, 61.5f);
    EXPECT_FLOAT_EQ(result.GetFirstColumn().w, 6.0f);

    EXPECT_FLOAT_EQ(result.GetSecondColumn().x, 10.0f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().y, 0.0f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().z, 2.5f);
    EXPECT_FLOAT_EQ(result.GetSecondColumn().w, 6.75f);

    EXPECT_FLOAT_EQ(result.GetThirdColumn().x, 21.5f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().y, 11.25f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().z, 18.25f);
    EXPECT_FLOAT_EQ(result.GetThirdColumn().w, 19.75f);

    EXPECT_FLOAT_EQ(result.GetFourthColumn().x, 18.75f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().y, 2.25f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().z, 22.25f);
    EXPECT_FLOAT_EQ(result.GetFourthColumn().w, 18.75f);
}


TEST(test_matrix_4, determinant) {
    const auto value_1 = core::matrix4<float>(15.0f, 0.0f, 24.6f, 2.4f, 4.0f, 0.0f, 1.0f, 2.7f, 8.6f, 4.5f, 7.3f, 7.9f, 7.5f, 0.9f, 8.9f, 7.5f);

    //result + expectations
    const auto result_1 = value_1.determinant();


    EXPECT_FLOAT_EQ(result_1, 1591.1478f);

    const auto value_2 = core::matrix4<int>(15, 0, 24, 2, 3, 4, 8, 30, 90, 50, 8, 0, 5, 6, 7, 2);

    //result + expectations
    const auto result_2 = value_2.determinant();


    EXPECT_EQ(result_2, 321848);
}


TEST(test_matrix_4, identity) {
    const auto actual = core::matrix4<int>::Identity();

    EXPECT_EQ(actual.GetFirstColumn().x, 1);
    EXPECT_EQ(actual.GetFirstColumn().y, 0);
    EXPECT_EQ(actual.GetFirstColumn().z, 0);
    EXPECT_EQ(actual.GetFirstColumn().w, 0);

    EXPECT_EQ(actual.GetSecondColumn().x, 0);
    EXPECT_EQ(actual.GetSecondColumn().y, 1);
    EXPECT_EQ(actual.GetSecondColumn().z, 0);
    EXPECT_EQ(actual.GetSecondColumn().w, 0);

    EXPECT_EQ(actual.GetThirdColumn().x, 0);
    EXPECT_EQ(actual.GetThirdColumn().y, 0);
    EXPECT_EQ(actual.GetThirdColumn().z, 1);
    EXPECT_EQ(actual.GetThirdColumn().w, 0);

    EXPECT_EQ(actual.GetFourthColumn().x, 0);
    EXPECT_EQ(actual.GetFourthColumn().y, 0);
    EXPECT_EQ(actual.GetFourthColumn().z, 0);
    EXPECT_EQ(actual.GetFourthColumn().w, 1);
}
