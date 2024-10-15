//
// Created by Mat on 15.10.2024.
//

#include <gtest/gtest.h>
#include "quaternion.h"
#include "vec3.h"

// Test for addition with int Quaternions
TEST(test_quaternion, addition_with_int)
{
    const Quaternion<int> q1(1, 2, 3, 4);
    const Quaternion<int> q2(4, 3, 2, 1);

    // Expected result: w = 5, x = 5, y = 5, z = 5
    const Quaternion<int> result = q1 + q2;
    const Quaternion<int> expected(5, 5, 5, 5);

    EXPECT_EQ(result.w, expected.w);
    EXPECT_EQ(result.x, expected.x);
    EXPECT_EQ(result.y, expected.y);
    EXPECT_EQ(result.z, expected.z);
}


// Test for subtraction with int Quaternions
TEST(test_quaternion, subtraction_with_int) {
    const Quaternion<int> q1(10, 10, 10, 10);
    const Quaternion<int> q2(4, 3, 2, 1);

    // Expected result: w = 6, x = 7, y = 8, z = 9
    const Quaternion<int> result = q1 - q2;
    const Quaternion<int> expected(6, 7, 8, 9);

    EXPECT_EQ(result.w, expected.w);
    EXPECT_EQ(result.x, expected.x);
    EXPECT_EQ(result.y, expected.y);
    EXPECT_EQ(result.z, expected.z);
}


TEST(test_quaternion, scalar_multiplication_with_float) {
    const Quaternion<float> q(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr float scalar = 2.0f;

    // Perform scalar multiplication
    const Quaternion<float> result = q * scalar;

    // Expected result: w = 2, x = 4, y = 6, z = 8
    const Quaternion<float> expected(2.0f, 4.0f, 6.0f, 8.0f);

    EXPECT_FLOAT_EQ(result.w, expected.w);
    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(result.z, expected.z);
}


TEST(test_quaternion, rotate_with_euler_angles) {
    // Euler angles: Yaw (Z), Pitch (Y), Roll (X)
    constexpr float yaw = PI / 4.0f;    // 45 degrees
    constexpr float pitch = PI / 6.0f;  // 30 degrees
    constexpr float roll = PI / 3.0f;   // 60 degrees

    // Perform the rotation from Euler angles
    const Quaternion<float> result(4.0, 5.0, 4.0, 6.0);

    const auto truc = result.Rotate(yaw, pitch, roll);

    // Expected quaternion calculated for the given Euler angles
    // These values are approximate based on the known quaternion conversion for Euler angles
    const Quaternion<float> expected(0.822363f, 0.36042339f, 0.39190382f, 0.20056212f);

    EXPECT_FLOAT_EQ(truc.w, expected.w);
    EXPECT_FLOAT_EQ(truc.x, expected.x);
    EXPECT_FLOAT_EQ(truc.y, expected.y);
    EXPECT_FLOAT_EQ(truc.z, expected.z);
}

// Test for quaternion conjugation with float Quaternions
TEST(test_quaternion, conjugate_with_float) {
    const Quaternion<float> q(1.0f, 2.0f, 3.0f, 4.0f);

    // Perform conjugation
    const Quaternion<float> result = q.Conjugate();

    const float normSq = q.norm() * q.norm();

    // Expected result: w stays the same, x, y, z are negated
    const Quaternion<float> expected(1.0f / normSq, -2.0f / normSq, -3.0f / normSq, -4.0f / normSq);

    EXPECT_FLOAT_EQ(result.w, expected.w);
    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(result.z, expected.z);
}

// Test for quaternion inversion with float Quaternions
TEST(test_quaternion, inverse_with_float) {
    const Quaternion<float> q(1.0f, 2.0f, 3.0f, 4.0f);

    // Perform inversion
    const Quaternion<float> result = q.Inverse();

    const Quaternion<float> expected(1.0f, -2.0f, -3.0f, -4.0f);

    EXPECT_FLOAT_EQ(result.w, expected.w);
    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(result.z, expected.z);
}

// Test for converting Euler angles to quaternion
TEST(test_quaternion, euler_to_quaternion_with_float) {
    constexpr  core::vec3<float> eulerAngles(0.0f, PI / 2.0f, 0.0f); // 90 degrees pitch rotation

    // Perform the rotation from Euler angles
    const Quaternion<float> result(5.0, 6.0, 4.0, 7.0);
    const auto truc = result.RotateFromEuler(eulerAngles);

    // Expected quaternion for 90 degrees around y-axis: (0.7071, 0, 0.7071, 0)
    const Quaternion<float> expected(0.7071f, 0.0f, 0.7071f, 0.0f);

    EXPECT_NEAR(truc.w, expected.w, 1e-4);
    EXPECT_NEAR(truc.x, expected.x, 1e-4);
    EXPECT_NEAR(truc.y, expected.y, 1e-4);
    EXPECT_NEAR(truc.z, expected.z, 1e-4);
}

// Test for converting quaternion to Euler angles
TEST(test_quaternion, quaternion_to_euler_with_float) {
    // Quaternion for 90 degrees around y-axis: (0.7071, 0, 0.7071, 0)
    const Quaternion<float> q(0.7071f, 0.0f, 0.7071f, 0.0f);

    // Convert quaternion to Euler angles
    const core::vec3<float> result = q.toEulerAngles();

    // Expected Euler angles: (0, 90 degrees, 0)
    constexpr core::vec3<float> expected(0.0f, 1.5645912, 0.0f); //the random number is a precise number equal to PI /2

    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(result.z, expected.z);
}


// Test for Vec3 to Quaternion conversion
TEST(test_quaternion, vec3_to_quaternion_with_float) {
    // Vec3 representing axis-angle (unit axis with angle magnitude)
    constexpr core::vec3<float> axisAngle(0.0f, 1.0f, 0.0f); // 1 radian rotation around the Y-axis

    // Convert Vec3 to Quaternion
    const Quaternion<float> result = Quaternion<float>::Vec3ToQuaternion(axisAngle);

    // Expected quaternion for 1 radian around Y-axis
    const float sinHalfAngle = std::sin(1.0f / 2.0f); // sin(1 radian / 2)
    const float cosHalfAngle = std::cos(1.0f / 2.0f); // cos(1 radian / 2)
    const Quaternion<float> expected(cosHalfAngle, 0.0f, sinHalfAngle, 0.0f);

    EXPECT_FLOAT_EQ(result.w, expected.w);
    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(result.z, expected.z);
}