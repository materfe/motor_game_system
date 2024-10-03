//
// Created by Mat on 30.09.2024.
//

#include "Vec4.h"
#include <gtest/gtest.h>



//what values it takes -> pair of Vec4f
struct Vec4fOperationFixture : public ::testing::TestWithParam<std::pair<core::Vec4<float>, core::Vec4<float>>>
{};

//test by itself -> add
TEST_P(Vec4fOperationFixture, add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;

	EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
	EXPECT_FLOAT_EQ(result.z, v1.z + v2.z);
	EXPECT_FLOAT_EQ(result.w, v1.w + v2.w);
}

//test by itself -> sub
TEST_P(Vec4fOperationFixture, sub)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;

	EXPECT_FLOAT_EQ(result.x, v1.x - v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y - v2.y);
	EXPECT_FLOAT_EQ(result.z, v1.z - v2.z);
	EXPECT_FLOAT_EQ(result.w, v1.w - v2.w);

	//nagative numbers
	const auto neg1 = -v1;
	const auto neg2 = -v2;

	EXPECT_FLOAT_EQ(neg1.x, -v1.x);
	EXPECT_FLOAT_EQ(neg1.y, -v1.y);
	EXPECT_FLOAT_EQ(neg1.z, -v1.z);
	EXPECT_FLOAT_EQ(neg1.w, -v1.w);

	EXPECT_FLOAT_EQ(neg2.x, -v2.x);
	EXPECT_FLOAT_EQ(neg2.y, -v2.y);
	EXPECT_FLOAT_EQ(neg2.z, -v2.z);
	EXPECT_FLOAT_EQ(neg2.w, -v2.w);
}

//test by itself -> multiply
TEST_P(Vec4fOperationFixture, multiply)
{
	auto [v1, v2] = GetParam();

	const auto p1 = v1 * 2.2f;
	const auto p2 = v2 * 2.5f;
	const auto p3 = 2.5f * v2;

	EXPECT_FLOAT_EQ(p1.x, v1.x * 2.2f);
	EXPECT_FLOAT_EQ(p1.y, v1.y * 2.2f);
	EXPECT_FLOAT_EQ(p1.z, v1.z * 2.2f);
	EXPECT_FLOAT_EQ(p1.w, v1.w * 2.2f);

	EXPECT_FLOAT_EQ(p2.x, v2.x * 2.5f);
	EXPECT_FLOAT_EQ(p2.y, v2.y * 2.5f);
	EXPECT_FLOAT_EQ(p2.z, v2.z * 2.5f);
	EXPECT_FLOAT_EQ(p2.w, v2.w * 2.5f);

	EXPECT_FLOAT_EQ(p3.x, v2.x * 2.5f);
	EXPECT_FLOAT_EQ(p3.y, v2.y * 2.5f);
	EXPECT_FLOAT_EQ(p3.z, v2.z * 2.5f);
	EXPECT_FLOAT_EQ(p3.w, v2.w * 2.5f);
}

//test by itself -> calculate division
TEST_P(Vec4fOperationFixture, divide)
{
	auto [v1, v2] = GetParam();

	const auto p1 = v1 / 2.2f;
	const auto p2 = v2 / 2.5f;
	const auto p3 = 2.5f / v1;

	EXPECT_FLOAT_EQ(p1.x, v1.x / 2.2f);
	EXPECT_FLOAT_EQ(p1.y, v1.y / 2.2f);
	EXPECT_FLOAT_EQ(p1.z, v1.z / 2.2f);
	EXPECT_FLOAT_EQ(p1.w, v1.w / 2.2f);

	EXPECT_FLOAT_EQ(p2.x, v2.x / 2.5f);
	EXPECT_FLOAT_EQ(p2.y, v2.y / 2.5f);
	EXPECT_FLOAT_EQ(p2.z, v2.z / 2.5f);
	EXPECT_FLOAT_EQ(p2.w, v2.w / 2.5f);

	EXPECT_FLOAT_EQ(p3.x, 2.5f / v1.x);
	EXPECT_FLOAT_EQ(p3.y, 2.5f / v1.y);
	EXPECT_FLOAT_EQ(p3.z, 2.5f / v1.z);
	EXPECT_FLOAT_EQ(p3.w, 2.5f / v1.w);
}

//test by itself -> dot product
TEST_P(Vec4fOperationFixture, dot_product) {
	auto [v1, v2] = GetParam();

	const auto result = core::Vec4<float>::Dot(v1, v2);

	EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

//test by itself -> calculate Lerp
TEST_P(Vec4fOperationFixture, lerp)
{
	//a.x + (b.x - a.x) * t
	auto [v1, v2] = GetParam();

	constexpr float t = 0.0f;
	const auto p1 = v1.Lerp(v1, v2, t);
	const auto p2 = v1.Lerp(v1, v2, 1.0f);

	EXPECT_FLOAT_EQ(p1.x, v1.x + (v2.x - v1.x) * t);
	EXPECT_FLOAT_EQ(p1.y, v1.y + (v2.y - v1.y) * t);
	EXPECT_FLOAT_EQ(p1.z, v1.z + (v2.z - v1.z) * t);
	EXPECT_FLOAT_EQ(p1.w, v1.w + (v2.w - v1.w) * t);


	if constexpr (t == 0.0f)
	{
		EXPECT_FLOAT_EQ(p1.x, v1.x);
		EXPECT_FLOAT_EQ(p1.y, v1.y);
		EXPECT_FLOAT_EQ(p1.z, v1.z);
		EXPECT_FLOAT_EQ(p1.w, v1.w);
	}
	else if constexpr (t == 1.0f)
	{
		EXPECT_FLOAT_EQ(p2.x, v2.x);
		EXPECT_FLOAT_EQ(p2.y, v2.y);
		EXPECT_FLOAT_EQ(p2.z, v2.z);
		EXPECT_FLOAT_EQ(p2.w, v2.w);
	}
}

//test by itself -> calculate Normalise vector
TEST_P(Vec4fOperationFixture, normalise)
{
	auto [v1, v2] = GetParam();

	const auto p1 = v1.Normalise();

	EXPECT_FLOAT_EQ(p1.x, v1.x / v1.Magnitude());
	EXPECT_FLOAT_EQ(p1.y, v1.y / v1.Magnitude());
	EXPECT_FLOAT_EQ(p1.z, v1.z / v1.Magnitude());
	EXPECT_FLOAT_EQ(p1.w, v1.w / v1.Magnitude());
}

//test by itself -> calculate Magnitude/SqrMagnitude
TEST_P(Vec4fOperationFixture, magnitude_and_sqrMagnitude)
{
	auto [v1, v2] = GetParam();

	const auto p1 = v1.Magnitude();
	const auto p2 = v2.SqrMagnitude();

	EXPECT_FLOAT_EQ(p1, std::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z + v1.w * v1.w));
	EXPECT_FLOAT_EQ(p2, v2.x * v2.x + v2.y * v2.y + v2.z * v2.z + v2.w * v2.w);
}


//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(Tests, Vec4fOperationFixture, testing::Values(
	std::pair{ core::Vec4<float>{1.3f,3.5f, 4.0f, 8.7f}, core::Vec4<float>{2.0f,4.8f, 0.0f, 5.6f} },
	std::pair{ core::Vec4<float>{1.5f,3.72f, 6.4f, 6.7f}, core::Vec4<float>{0.0f,0.0f, 0.0f, 0.0f} }));




//test -> test if crashes on certain operations (division by 0)
TEST(test_vec4f, crash_test_division) {
	constexpr auto vec_1 = core::Vec4<float>{1.3f,3.5f, 5.0f, 6.7f};
	constexpr float factor = 0.0f;

	//if divisor == 0 -> crash
	EXPECT_EXIT(vec_1 / factor, ::testing::ExitedWithCode(3), "");

	//all vectors used as scalars (to test if it crashes or not)
	constexpr auto vec_2 = core::Vec4<float>{0.0f, 5.0f, 3.8f, 7.9f};
	constexpr auto vec_3 = core::Vec4<float>{5.0f, 0.0f, 4.6f, 7.9f};
	constexpr auto vec_4 = core::Vec4<float>{5.0f, 8.0f, 0.0f, 8.2f};
	constexpr auto vec_5 = core::Vec4<float>{5.0f, 8.0f, 7.0f, 0.0f};
	constexpr auto vec_6 = core::Vec4<float>{0.0f, 0.0f, 0.0f, 0.0f};

	//if vec.x or vec.y == 0 and divide in the other order -> crash
	EXPECT_EXIT(factor / vec_2, ::testing::ExitedWithCode(3), ""); //if vec.x == 0 -> crash
	EXPECT_EXIT(factor / vec_3, ::testing::ExitedWithCode(3), ""); //if vec.y == 0 -> crash
	EXPECT_EXIT(factor / vec_4, ::testing::ExitedWithCode(3), ""); //if vec.z == 0 -> crash
	EXPECT_EXIT(factor / vec_5, ::testing::ExitedWithCode(3), ""); //if vec.w == 0 -> crash
	EXPECT_EXIT(factor / vec_6, ::testing::ExitedWithCode(3), ""); //if vec.x.y.z.w == 0 -> crash
}

//test crash division in normalise()
TEST(test_vec4f, crash_test_division_when_normalising) {
	constexpr auto vec_3 = core::Vec4{0.0f, 0.0f, 0.0f, 0.0f};

	EXPECT_EXIT(vec_3.Normalise(), ::testing::ExitedWithCode(3), "");
}