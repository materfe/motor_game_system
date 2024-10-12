//
// Created by Mat on 26.09.2024.
//


#include <vec2.h>
#include <gtest/gtest.h>


//what values it takes -> pair of Vec2f
struct Vec2OperationFixture : public ::testing::TestWithParam<std::pair<core::vec2<float>, core::vec2<float> > > {
};

//test by itself -> add
TEST_P(Vec2OperationFixture, add) {
    auto [v1, v2] = GetParam();
    const auto result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x_, v1.x_ + v2.x_);
    EXPECT_FLOAT_EQ(result.y_, v1.y_ + v2.y_);

    const auto test = core::vec2<float>(8.0f, 7.6f);
    const auto test_other = core::vec2<float>(0.0f, 90.0f);
    const auto result_2 = test + test_other;

    EXPECT_FLOAT_EQ(result_2.x_, 8.0f + 0.0f);
    EXPECT_FLOAT_EQ(result_2.y_, 7.6f + 90.0f);
}

//test by itself -> sub
TEST_P(Vec2OperationFixture, sub) {
    //substraction
    auto [v1, v2] = GetParam();
    const auto result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x_, v1.x_ - v2.x_);
    EXPECT_FLOAT_EQ(result.y_, v1.y_ - v2.y_);

    //nagative numbers
    const auto neg1 = -v1;
    const auto neg2 = -v2;
    EXPECT_FLOAT_EQ(neg1.x_, -v1.x_);
    EXPECT_FLOAT_EQ(neg2.x_, -v2.x_);
}

//test by itself -> calculate perpendicular
TEST_P(Vec2OperationFixture, perpendicular) {
    //substraction
    auto [v1, v2] = GetParam();
    const auto p1 = v1.Perpendicular();
    const auto p2 = v2.Perpendicular();
    EXPECT_FLOAT_EQ(core::vec2<float>::Dot(v1, p1), 0);
    EXPECT_FLOAT_EQ(core::vec2<float>::Dot(v2, p2), 0);
}

//test by itself -> dot_product
TEST_P(Vec2OperationFixture, dot_product) {
    auto [v1, v2] = GetParam();

    const auto result = core::vec2<float>::Dot(v1, v2);

    EXPECT_FLOAT_EQ(result, v1.x_ * v2.x_ + v1.y_ * v2.y_);
}

//test by itself -> multiply
TEST_P(Vec2OperationFixture, multiply) {
    //substraction
    auto [v1, v2] = GetParam();
    const auto p1 = v1 * 2.2f;
    const auto p2 = v2 * 2.5f;
    //const auto p3 = 2.5f * v2;

    EXPECT_FLOAT_EQ(p1.x_, v1.x_ * 2.2f);
    EXPECT_FLOAT_EQ(p1.y_, v1.y_ * 2.2f);
    EXPECT_FLOAT_EQ(p2.x_, v2.x_ * 2.5f);
    EXPECT_FLOAT_EQ(p2.y_, v2.y_ * 2.5f);

    //EXPECT_FLOAT_EQ(p3.y, v2.y * 2.5f);
    //EXPECT_FLOAT_EQ(p3.x, v2.x * 2.5f);
}

//test by itself -> calculate division
TEST_P(Vec2OperationFixture, divide) {
    //substraction
    auto [v1, v2] = GetParam();
    const auto p1 = v1 / 2.2f;
    const auto p2 = v2 / 2.5f;
    //const auto p3 = 2.5f / v1;

    EXPECT_FLOAT_EQ(p1.x_, v1.x_ / 2.2f);
    EXPECT_FLOAT_EQ(p1.y_, v1.y_ / 2.2f);

    EXPECT_FLOAT_EQ(p2.x_, v2.x_ / 2.5f);
    EXPECT_FLOAT_EQ(p2.y_, v2.y_ / 2.5f);

    //EXPECT_FLOAT_EQ(p3.x, 2.5f / v1.x);
    //EXPECT_FLOAT_EQ(p3.y, 2.5f / v1.y);
}

//test by itself -> calculate Lerp
TEST_P(Vec2OperationFixture, lerp) {
    //substraction a.x + (b.x - a.x) * t
    auto [v1, v2] = GetParam();
    constexpr float t = 0.0f;
    const auto p1 = v1.Lerp(v1, v2, t);
    const auto p2 = v1.Lerp(v1, v2, t + 1.0f);
    EXPECT_FLOAT_EQ(p1.x_, v1.x_ + (v2.x_ - v1.x_) * t);
    EXPECT_FLOAT_EQ(p1.y_, v1.y_ + (v2.y_ - v1.y_) * t);


    if constexpr (t == 0.0f) {
        EXPECT_FLOAT_EQ(p1.x_, v1.x_);
    } else if constexpr (t == 1.0f) {
        EXPECT_FLOAT_EQ(p2.x_, v2.x_);
    }
}

//test by itself -> calculate Normalise vector
TEST_P(Vec2OperationFixture, normalise) {
    auto [v1, v2] = GetParam();
    const auto p1 = v1.Normalise();

    EXPECT_FLOAT_EQ(p1.x_, v1.x_ / v1.Magnitude());
    EXPECT_FLOAT_EQ(p1.y_, v1.y_ / v1.Magnitude());
}

//test by itself -> calculate Magnitude/SqrMagnitude
TEST_P(Vec2OperationFixture, magnitude_and_sqrMagnitude) {
    auto [v1, v2] = GetParam();
    const auto p1 = v1.Magnitude();
    const auto p2 = v2.SqrMagnitude();

    const auto dot1 = core::vec2<float>::Dot(v1, v1);
    const auto dot2 = core::vec2<float>::Dot(v2, v2);

    EXPECT_FLOAT_EQ(p1, std::sqrt(dot1));
    EXPECT_FLOAT_EQ(p2, dot2);

    if (p1 != 0) {
        const auto v_unit1 = v1 / p1;
        EXPECT_FLOAT_EQ(v_unit1.Magnitude(), 1.0f);
    }
}


//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(tests, Vec2OperationFixture, testing::Values(
                             std::pair{ core::vec2<float>{1.3f,3.5f}, core::vec2<float>{2.0f,4.8f} },
                             std::pair{ core::vec2<float>{1.5f,3.72f}, core::vec2<float>{0.0f,0.0f} }));

//test if it crashes when dividing by 0
TEST(test_vec2f, crash_test_division) {
    constexpr auto vec_1 = core::vec2<float>{1.3f, 3.5f};
    constexpr float factor = 0.0f;

    //if divisor == 0 -> crash
    EXPECT_EXIT(vec_1 / factor, ::testing::ExitedWithCode(3), "");

    constexpr auto vec_2 = core::vec2<float>{0.0f, 5.0f};
    constexpr auto vec_3 = core::vec2<float>{5.0f, 0.0f};
    constexpr auto vec_4 = core::vec2<float>{0.0f, 0.0f};

    //if vec.x or vec.y == 0 and divide in the other order -> crash
    EXPECT_EXIT(factor / vec_2, ::testing::ExitedWithCode(3), ""); //vec.x == 0 -> crash
    EXPECT_EXIT(factor / vec_3, ::testing::ExitedWithCode(3), ""); //vec.y == 0 -> crash
    EXPECT_EXIT(factor / vec_4, ::testing::ExitedWithCode(3), ""); //vec.x.y == 0 -> crash
}

//test crash division in normalise()
TEST(test_vec2f, crash_test_division_when_normalising) {
    constexpr auto vec_3 = core::vec2<float>{0.0f, 0.0f};

    EXPECT_EXIT(const auto n = vec_3.Normalise(), ::testing::ExitedWithCode(3), "");
}

TEST(test_vec2f, crash_test_operator_) {
    constexpr auto vec_1 = core::vec2<float>{1.3f, 3.5f};

    EXPECT_EXIT(vec_1[3], ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(vec_1[-1], ::testing::ExitedWithCode(3), "");
}


TEST(test_vec2f, test_operator_) {
    constexpr auto vec_1 = core::vec2<float>{1.3f, 3.5f};

    EXPECT_EQ(vec_1[0], 1.3f);
    EXPECT_EQ(vec_1[1], 3.5f);
}
