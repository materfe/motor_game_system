//
// Created by Mat on 30.09.2024.
//

#include <vec3.h>
#include <gtest/gtest.h>


//what values it takes -> pair of Vec2f
struct Vec3fOperationFixture : public ::testing::TestWithParam<std::pair<core::Vec3<float>, core::Vec3<float>>>
{};

//test by itself -> add
TEST_P(Vec3fOperationFixture, add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;

	EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
	EXPECT_FLOAT_EQ(result.z, v1.z + v2.z);
}

//test by itself -> sub
TEST_P(Vec3fOperationFixture, sub)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;

	EXPECT_FLOAT_EQ(result.x, v1.x - v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y - v2.y);
	EXPECT_FLOAT_EQ(result.z, v1.z - v2.z);

	//nagative numbers
	const auto neg1 = -v1;
	const auto neg2 = -v2;

	EXPECT_FLOAT_EQ(neg1.x, -v1.x);
	EXPECT_FLOAT_EQ(neg1.y, -v1.y);
	EXPECT_FLOAT_EQ(neg1.z, -v1.z);

	EXPECT_FLOAT_EQ(neg2.x, -v2.x);
	EXPECT_FLOAT_EQ(neg2.y, -v2.y);
	EXPECT_FLOAT_EQ(neg2.z, -v2.z);
}

//test by itself -> multiply
TEST_P(Vec3fOperationFixture, multiply)
{
	auto [v1, v2] = GetParam();

	const auto p1 = v1 * 2.2f;
	const auto p2 = v2 * 2.5f;
	const auto p3 = 2.5f * v2;

	EXPECT_FLOAT_EQ(p1.x, v1.x * 2.2f);
	EXPECT_FLOAT_EQ(p1.y, v1.y * 2.2f);
	EXPECT_FLOAT_EQ(p1.z, v1.z * 2.2f);

	EXPECT_FLOAT_EQ(p2.x, v2.x * 2.5f);
	EXPECT_FLOAT_EQ(p2.y, v2.y * 2.5f);
	EXPECT_FLOAT_EQ(p2.z, v2.z * 2.5f);

	EXPECT_FLOAT_EQ(p3.x, v2.x * 2.5f);
	EXPECT_FLOAT_EQ(p3.y, v2.y * 2.5f);
	EXPECT_FLOAT_EQ(p3.z, v2.z * 2.5f);
}

//test by itself -> calculate division
TEST_P(Vec3fOperationFixture, divide)
{
	auto [v1, v2] = GetParam();

	const auto p1 = v1 / 2.2f;
	const auto p2 = v2 / 2.5f;
	const auto p3 = 2.5f / v1;

	EXPECT_FLOAT_EQ(p1.x, v1.x / 2.2f);
	EXPECT_FLOAT_EQ(p1.y, v1.y / 2.2f);
	EXPECT_FLOAT_EQ(p1.z, v1.z / 2.2f);

	EXPECT_FLOAT_EQ(p2.x, v2.x / 2.5f);
	EXPECT_FLOAT_EQ(p2.y, v2.y / 2.5f);
	EXPECT_FLOAT_EQ(p2.z, v2.z / 2.5f);

	EXPECT_FLOAT_EQ(p3.x, 2.5f / v1.x);
	EXPECT_FLOAT_EQ(p3.y, 2.5f / v1.y);
	EXPECT_FLOAT_EQ(p3.z, 2.5f / v1.z);
}

//test by itself -> dot product
TEST_P(Vec3fOperationFixture, dot_product) {
	auto [v1, v2] = GetParam();

	const auto result = core::Vec3<float>::Dot(v1, v2);

	EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

//test by itself -> cross product
TEST_P(Vec3fOperationFixture, cross_product) {
	auto [v1, v2] = GetParam();

	const auto result = core::Vec3<float>::Cross(v1, v2);

	EXPECT_FLOAT_EQ(result.x, v1.y * v2.z - v1.z * v2.y);
	EXPECT_FLOAT_EQ(result.y, v1.z * v2.x - v1.x * v2.z);
	EXPECT_FLOAT_EQ(result.z, v1.x * v2.y - v1.y * v2.x);
}

//test by itself -> calculate Lerp
TEST_P(Vec3fOperationFixture, lerp)
{
	//a.x + (b.x - a.x) * t
	auto [v1, v2] = GetParam();

	constexpr float t = 0.0f;
	const auto p1 = v1.Lerp(v1, v2, t);
	const auto p2 = v1.Lerp(v1, v2, 1.0f);

	EXPECT_FLOAT_EQ(p1.x, v1.x + (v2.x - v1.x) * t);
	EXPECT_FLOAT_EQ(p1.y, v1.y + (v2.y - v1.y) * t);
	EXPECT_FLOAT_EQ(p1.z, v1.z + (v2.z - v1.z) * t);


	if constexpr (t == 0.0f)
	{
		EXPECT_FLOAT_EQ(p1.x, v1.x);
		EXPECT_FLOAT_EQ(p1.y, v1.y);
		EXPECT_FLOAT_EQ(p1.z, v1.z);
	}
	else if constexpr (t == 1.0f)
	{
		EXPECT_FLOAT_EQ(p2.x, v2.x);
		EXPECT_FLOAT_EQ(p2.y, v2.y);
		EXPECT_FLOAT_EQ(p2.z, v2.z);
	}
}

//test by itself -> calculate Normalise vector
TEST_P(Vec3fOperationFixture, normalise)
{
	auto [v1, v2] = GetParam();

	const auto p1 = v1.Normalise();

	EXPECT_FLOAT_EQ(p1.Magnitude(), 1.0f);
}

//test by itself -> calculate Magnitude/SqrMagnitude
TEST_P(Vec3fOperationFixture, magnitude_and_sqrMagnitude)
{
	auto [v1, v2] = GetParam();

	const auto p1 = v1.Magnitude();
	const auto p2 = v2.SqrMagnitude();

	EXPECT_FLOAT_EQ(p1, std::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
	EXPECT_FLOAT_EQ(p2, v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
}


//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(Tests, Vec3fOperationFixture, testing::Values(
	std::pair{core::Vec3{1.3f, 3.5f, 4.0f}, core::Vec3{2.0f, 4.8f, 8.0f} },
	std::pair{core::Vec3{1.5f, 3.72f, 6.4f}, core::Vec3{0.0f, 0.0f, 0.0f} }));

//test -> test if crashes on certain operations (division by 0)
TEST(test_vec3f, crash_test_division) {
	constexpr auto vec_1 = core::Vec3{1.3f, 3.5f, 5.0f};
	constexpr float factor = 0.0f;

	//if divisor == 0 -> crash
	EXPECT_EXIT(vec_1 / factor, ::testing::ExitedWithCode(3), "");

	constexpr auto vec_2 = core::Vec3{0.0f, 5.0f, 3.8f};
	constexpr auto vec_3 = core::Vec3{5.0f, 0.0f, 4.6f};
	constexpr auto vec_4 = core::Vec3{5.0f, 8.0f, 0.0f};
	constexpr auto vec_5 = core::Vec3{0.0f, 0.0f, 0.0f};

	//if vec.x or vec.y == 0 and divide in the other order -> crash
	EXPECT_EXIT(factor / vec_2, ::testing::ExitedWithCode(3), ""); //if vec.x == 0 -> crash
	EXPECT_EXIT(factor / vec_3, ::testing::ExitedWithCode(3), ""); //if vec.y == 0 -> crash
	EXPECT_EXIT(factor / vec_4, ::testing::ExitedWithCode(3), ""); //if vec.z == 0 -> crash
	EXPECT_EXIT(factor / vec_5, ::testing::ExitedWithCode(3), ""); //if vec.x.y.z == 0 -> crash
}

//test crash division in normalise()
TEST(test_vec3f, crash_test_division_when_normalising) {
	constexpr auto vec_3 = core::Vec3{0.0f, 0.0f, 0.0f};

	EXPECT_EXIT(const auto truc = vec_3.Normalise(), ::testing::ExitedWithCode(3), "");
}

TEST(test_vec3f, crash_test_operator_) {
	constexpr auto vec_1 = core::Vec3<float>{1.3f, 3.5f, 4.0f};

	EXPECT_EXIT(vec_1[3], ::testing::ExitedWithCode(3), "");
	EXPECT_EXIT(vec_1[-1], ::testing::ExitedWithCode(3), "");
}


TEST(test_vec3f, test_operator_) {
	constexpr auto vec_1 = core::Vec3<float>{1.3f, 3.5f, 4.0f};

	EXPECT_EQ(vec_1[0], 1.3f);
	EXPECT_EQ(vec_1[1], 3.5f);
	EXPECT_EQ(vec_1[2], 4.0f);
}