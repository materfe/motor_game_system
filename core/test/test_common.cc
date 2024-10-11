//
// Created by Mat on 11.10.2024.
//


#include "common.h"
#include <gtest/gtest.h>


TEST(common_test, epsilon) {
    constexpr auto epsilon = EPSILON;

    EXPECT_EQ(epsilon, 2.2204460492503131e-016f);

    constexpr auto epsilon2 = 2.2204460492503131e-016f;
    constexpr auto result = epsilon2 - epsilon;

    EXPECT_EQ(result, 0.0f);
}


TEST(common_test, pi) {
    constexpr auto epsilon = PI;

    EXPECT_EQ(epsilon, 3.14159265358979323846f);

    constexpr auto epsilon2 = 3.14159265358979323846f;
    constexpr auto result = epsilon2 - epsilon;

    EXPECT_EQ(result, 0.0f);
}


TEST(common_test, aproximate) {
    constexpr auto value = 0.2f;

    const auto approximate = common::AproximateZeroForFloats(value);
    bool compare = false;

    EXPECT_EQ(approximate, compare);

    const auto approximate2 = common::AproximateZeroForFloats(0.0f);
    compare = true;

    EXPECT_EQ(approximate2, compare);
}


TEST(common_test, to_meters) {
    constexpr auto value = 80.0f;

    auto result = common::ToMeters(value);

    EXPECT_EQ(result, 0.8f);

    result = common::ToMeters(0.0f);

    EXPECT_EQ(result, 0.0f);
}


TEST(common_test, to_pixels) {
    constexpr auto value = 80.0f;

    auto result = common::ToPixels(value);

    EXPECT_EQ(result, 8000.0f);

    result = common::ToPixels(0.0f);

    EXPECT_EQ(result, 0.0f);
}


TEST(common_test, to_degrees) {
    constexpr auto value = PI / 2.0f;

    auto result = common::ToDegree(value);

    EXPECT_EQ(result, 90.0f);

    result = common::ToDegree(0.0f);

    EXPECT_EQ(result, 0.0f);
}


TEST(common_test, to_radians) {
    constexpr auto value = 90.0f;

    auto result = common::ToRadians(value);

    EXPECT_EQ(result, PI / 2.0f);

    result = common::ToRadians(0.0f);

    EXPECT_EQ(result, 0.0f);
}
