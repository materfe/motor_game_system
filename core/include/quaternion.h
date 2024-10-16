//
// Created by Mat on 12.10.2024.
//

#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include "vec3.h"
#include "common.h"

template <typename T>
struct Quaternion {
    T w, x, y, z; // Components of the quaternion

    // Constructor to initialize quaternion with specific values
    Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

    // Copy constructor
    Quaternion(const Quaternion& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}

    // Addition of two quaternions
    constexpr Quaternion operator+(const Quaternion& q) const {
        return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
    }

    // Subtraction of two quaternions
    constexpr Quaternion operator-(const Quaternion& q) const {
        return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
    }

    // Scalar multiplication
    constexpr Quaternion operator*(T scalar) const {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    // Norm (magnitude) of the quaternion
    T norm() const {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    // Conjugate of the quaternion
    Quaternion Inverse() const {
        return Quaternion(w, -x, -y, -z);
    }

    // Inverse of the quaternion (q^-1 = q* / ||q||^2)
    Quaternion Conjugate() const {
        T n = norm();
        if (n == 0) {
            std::terminate();
        }
        return Inverse() * (1.0f/ (n * n));
    }

    // Rotation using Euler angles (yaw, pitch, roll) in radians
    Quaternion Rotate(T yaw, T pitch, T roll) const {
        T cy = std::cos(yaw * 0.5);
        T sy = std::sin(yaw * 0.5);
        T cp = std::cos(pitch * 0.5);
        T sp = std::sin(pitch * 0.5);
        T cr = std::cos(roll * 0.5);
        T sr = std::sin(roll * 0.5);

        return Quaternion(
            cr * cp * cy + sr * sp * sy,   // w component
            sr * cp * cy - cr * sp * sy,   // x component
            cr * sp * cy + sr * cp * sy,   // y component
            cr * cp * sy - sr * sp * cy    // z component
        );
    }

    // Method to rotate using Euler angles provided as Vec3
    Quaternion<T> RotateFromEuler(const core::Vec3<T>& eulerAngles) const {
        return Rotate(eulerAngles.z, eulerAngles.y, eulerAngles.x);
    }

    // Convert a Vec3 (axis-angle) into a quaternion (assuming Vec3 represents axis and angle magnitude as radians)
    static Quaternion Vec3ToQuaternion(const core::Vec3<T>& v) {
        T angle = static_cast<float>(v.Magnitude());
        if (common::AproximateZeroForFloats(angle)) {
            return Quaternion(1, 0, 0, 0);
        }

        const T sinHalfAngle = std::sin(angle / 2.0);
        const T cosHalfAngle = std::cos(angle / 2.0);

        return Quaternion(
            cosHalfAngle,                   // w component
            (v.x / angle) * sinHalfAngle,   // x component
            (v.y / angle) * sinHalfAngle,   // y component
            (v.z / angle) * sinHalfAngle    // z component
        );
    }

    // Convert quaternion to Euler angles in radians, returned as Vec3 (roll, pitch, yaw)
    core::Vec3<T> toEulerAngles() const {
        core::Vec3<T> eulerAngles;

        // Roll (x-axis rotation)
        const T sinr_cosp = 2 * (w * x + y * z);
        const T cosr_cosp = 1 - 2 * (x * x + y * y);
        eulerAngles.x = std::atan2(sinr_cosp, cosr_cosp);

        // Pitch (y-axis rotation)
        const T sinp = 2 * (w * y - z * x);
        if (std::abs(sinp) >= 1)
            eulerAngles.y = std::copysign(PI / 2, sinp); // Use 90 degrees if out of range
        else
            eulerAngles.y = std::asin(sinp);

        // Yaw (z-axis rotation)
        const T siny_cosp = 2 * (w * z + x * y);
        const T cosy_cosp = 1 - 2 * (y * y + z * z);
        eulerAngles.z = std::atan2(siny_cosp, cosy_cosp);

        return eulerAngles;
    }
};

#endif //QUATERNION_H
