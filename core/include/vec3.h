﻿//
// Created by Mat on 30.09.2024.
//

#ifndef VEC3F_H
#define VEC3F_H

#include <cmath>
#include <complex>

namespace core
{
	/**
	 * \brief Vec3f is a struct that allows basic math operations in 3D space
	 */
	template <typename T>
	struct Vec3
	{
		T x = 0, y = 0, z = 0;

		//set zero() to set vec to zero
		static constexpr Vec3 Zero() { return Vec3{}; }

		// Addition operator
		constexpr Vec3 operator+(Vec3 other) const
		{
			return { x + other.x, y + other.y, z + other.z };
		}

		// Subtraction operator
		constexpr Vec3 operator-(Vec3 other) const
		{
			return { x - other.x, y - other.y, z - other.z };
		}

		// Negation operator
		constexpr Vec3 operator-() const
		{
			return { -x, -y, -z };
		}

		// Multiply by scalar
		constexpr Vec3 operator*(T scalar) const
		{
			return { x * scalar, y * scalar, z * scalar };
		}

		constexpr T operator[](const int index) const {
			if (index < 0 || index > 2) {
				std::terminate();
			}
			if (index == 0) {
				return x;
			}
			if (index == 1) {
				return y;
			}
			return z;
		}


		// Divide by scalar
		constexpr Vec3 operator/(T scalar) const
		{
			const int scalar_int = static_cast<int>(scalar);
			if (scalar_int == 0)
			{
				std::terminate();
			}
			else
			{
				return { x / scalar, y / scalar, z / scalar };
			}
		}

		// Dot product (produit scalaire)
		static constexpr T Dot(Vec3 v1, Vec3 v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		// Cross product
		static constexpr Vec3 Cross(Vec3 v1, Vec3 v2)
		{
			return {
				v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x
			};
		}

		// Lerp (linear interpolation)
		[[nodiscard]] static constexpr Vec3 Lerp(Vec3 a, Vec3 b, float t)
		{
			return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t };
		}

		// Normalize the vector
		[[nodiscard]] Vec3 Normalise() const
		{
			const T magnitude = Magnitude();
			if(magnitude == 0 ) {
				std::terminate();
			}

			const T norm_x = x == 0 ? 0 : x / magnitude;
			const T norm_y = y == 0 ? 0 : y / magnitude;
			const T norm_z = z == 0 ? 0 : z / magnitude;
			return { norm_x, norm_y, norm_z };
		}

		// Magnitude (length of the vector)
		[[nodiscard]] T Magnitude() const
		requires std::is_floating_point_v<T>
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		// Squared Magnitude (avoiding square root for faster calculations)
		[[nodiscard]] constexpr T SqrMagnitude() const
		{
			return x * x + y * y + z * z;
		}

	}; //struct Vec3f

	template <typename T>
	constexpr Vec3<T> operator*(const float t, const Vec3<T>& vec)
	{
		return { t * vec.x, t * vec.y, t * vec.z };
	}

	template <typename T>
	constexpr Vec3<T> operator/(const float t, const Vec3<T>& vec)
	{
		if (vec.x == 0 || vec.y == 0 || vec.z == 0) {
			std::terminate();
		}

		return { t / vec.x, t / vec.y, t / vec.z };
	}

} // namespace core

#endif //VEC3F_H
