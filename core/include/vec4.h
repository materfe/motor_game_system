//
// Created by Mat on 30.09.2024.
//

#ifndef VEC4F_H
#define VEC4F_H

#include <cmath>
#include <complex>

namespace core
{
	/**
	 * \brief Vec4f is a struct that allows operations in 4D space (lol what is 4D)
	 */
	template <typename T>
	struct Vec4
	{
		T x = 0, y = 0, z = 0, w = 0;

		template<typename Other_T>

		//set zero() to set vec to zero
		static constexpr Vec4 Zero() { return Vec4{}; }

		// Addition operator
		constexpr Vec4 operator+(Vec4 other) const
		{
			return { x + other.x, y + other.y, z + other.z, w + other.w };
		}

		// Subtraction operator
		constexpr Vec4 operator-(Vec4 other) const
		{
			return { x - other.x, y - other.y, z - other.z, w - other.w };
		}

		// Negation operator
		constexpr Vec4 operator-() const
		{
			return { -x, -y, -z, -w };
		}

		// Multiply by scalar
		constexpr Vec4 operator*(T scalar) const
		{
			return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		constexpr T operator[](const int index) const {
			if (index < 0 || index > 3) {
				std::terminate();
			}
			if (index == 0) {
				return x;
			}
			if (index == 1) {
				return y;
			}
			if (index == 2) {
				return z;
			}
			return w;
		}


		// Divide by scalar
		constexpr Vec4 operator/(const T scalar) const
		{
			const int scalar_int = static_cast<int>(scalar);
			if (scalar_int == 0)
			{
				std::terminate();
			}
			else
			{
				return { x / scalar, y / scalar, z / scalar, w / scalar };
			}
		}

		// Dot product (produit scalaire)
		static constexpr T Dot(Vec4 v1, Vec4 v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
		}

		// Lerp (linear interpolation)
		[[nodiscard]] static constexpr Vec4 Lerp(Vec4 a, Vec4 b, float t)
		{
			return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t };
		}

		// Normalize the vector
		[[nodiscard]] Vec4 Normalise() const
		{
			const T magnitude = Magnitude();
			if(magnitude == 0) {
				std::terminate();
			}

			const T norm_x = x == 0 ? 0 : x / magnitude;
			const T norm_y = y == 0 ? 0 : y / magnitude;
			const T norm_z = z == 0 ? 0 : z / magnitude;
			const T norm_w = w == 0 ? 0 : w / magnitude;
			return { norm_x, norm_y, norm_z, norm_w };
		}

		// Magnitude (length of the vector)
		[[nodiscard]] T Magnitude() const
		requires std::is_floating_point_v<T>
		{
			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		// Squared Magnitude (avoiding square root for faster calculations)
		[[nodiscard]] constexpr T SqrMagnitude() const
		{
			return x * x + y * y + z * z + w * w;
		}

	}; //struct Vec3f

	template <typename T>
	constexpr Vec4<T> operator*(const T t, const Vec4<T>& vec)
	{
		return { t * vec.x, t * vec.y, t * vec.z, t * vec.w };
	}

	template <typename T>
	constexpr Vec4<T> operator/(const T t, const Vec4<T>& vec)
	{
		if (vec.x == 0 || vec.y == 0 || vec.z == 0 || vec.w == 0) {
			std::terminate();
		}

		return { t / vec.x, t / vec.y, t / vec.z, t / vec.w };
	}

} // namespace core

#endif //VEC4F_H
