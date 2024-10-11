//
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
	struct vec3
	{
		T x = 0, y = 0, z = 0;

		//set zero() to set vec to zero
		static constexpr vec3 Zero() { return vec3{}; }

		// Addition operator
		constexpr vec3 operator+(vec3 other) const
		{
			return { x + other.x, y + other.y, z + other.z };
		}

		// Subtraction operator
		constexpr vec3 operator-(vec3 other) const
		{
			return { x - other.x, y - other.y, z - other.z };
		}

		// Negation operator
		constexpr vec3 operator-() const
		{
			return { -x, -y, -z };
		}

		// Multiply by scalar
		constexpr vec3 operator*(T scalar) const
		{
			return { x * scalar, y * scalar, z * scalar };
		}

		// Divide by scalar
		constexpr vec3 operator/(T scalar) const
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
		static constexpr T Dot(vec3 v1, vec3 v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		// Cross product
		static constexpr vec3 Cross(vec3 v1, vec3 v2)
		{
			return {
				v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x
			};
		}

		// Lerp (linear interpolation)
		[[nodiscard]] static constexpr vec3 Lerp(vec3 a, vec3 b, float t)
		{
			return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t };
		}

		// Normalize the vector
		[[nodiscard]] vec3 Normalise() const
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
	constexpr vec3<T> operator*(const float t, const vec3<T>& vec)
	{
		return { t * vec.x, t * vec.y, t * vec.z };
	}

	template <typename T>
	constexpr vec3<T> operator/(const float t, const vec3<T>& vec)
	{
		if (vec.x == 0 || vec.y == 0 || vec.z == 0) {
			std::terminate();
		}

		return { t / vec.x, t / vec.y, t / vec.z };
	}

} // namespace core

#endif //VEC3F_H
