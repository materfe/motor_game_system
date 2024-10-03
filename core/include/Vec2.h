//
// Created by Mat on 26.09.2024.
//

#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_
#include <cmath>
#include <complex>

namespace core {
    /**
     * \brief Vec2f is a struct that allow basic maths
     */
    template <typename T>
    struct Vec2 {
        T x = 0, y = 0;

        //set zero() to set vec to zero
        static constexpr Vec2 Zero() { return Vec2{}; }


        //add system
        constexpr Vec2 operator+(Vec2 other) const {
            return {x + other.x, y + other.y};
        }

        //sub system
        constexpr Vec2 operator-(Vec2 other) const {
            return {x - other.x, y - other.y};
        }

        //negative numbers system
        constexpr Vec2 operator-() const {
            return {-x, -y};
        }

        //multiply
        constexpr Vec2 operator*(float scalaire) const {
            return {x * scalaire, y * scalaire};
        }

        //divide
        constexpr Vec2 operator/(float scalar) const {
            const int scalar_int = static_cast<int>(scalar);
            if (scalar_int == 0) {
                std::terminate();
            } else {
                return {x / scalar, y / scalar};
            }
        }

        //dot product (produit scalare) system
        static constexpr T Dot(Vec2 v1, Vec2 v2) {
            return v1.x * v2.x + v1.y * v2.y;
        }

        //perpenducular
        [[nodiscard]] constexpr Vec2 Perpendicular() const //FAIRE perpendicular 2
        {
            return {-y, x};
        }

        //perpendicular 2
        [[nodiscard]] constexpr Vec2 Perpendicular2() const //FAIRE perpendicular 2
        {
            return {y, -x};
        }

        //Lerp
        [[nodiscard]] static constexpr Vec2 Lerp(Vec2 a, Vec2 b, float t) {
            return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
        }

        //normalise and sqr normalise your vector
        [[nodiscard]] Vec2 Normalise() const {
            const T magnitude = Magnitude();
            if(magnitude == 0) {
                std::terminate();
            }

            const T norm_x = x == 0 ? 0 : x / magnitude;
            const T norm_y = y == 0 ? 0 : y / magnitude;
            return {norm_x, norm_y};
        }


        //calculate magnitude and sqr magnitude
        [[nodiscard]] T Magnitude() const
        requires std::is_floating_point_v<T>
        {
            const float length = std::sqrt(x * x + y * y);
            return length;
        }

        [[nodiscard]] constexpr T SqrMagnitude() const {
            const float length = x * x + y * y;
            return length;
        }
    }; //struct Vec2f

    template <typename T>
    constexpr Vec2<T> operator*(const float t, const Vec2<T> &vec) {
        return {t * vec.x, t * vec.y};
    }

    template <typename T>
    constexpr Vec2<T> operator/(const float t, const Vec2<T> &vec) {
        if (vec.x == 0 || vec.y == 0) {
            std::terminate();
        }

        return {t / vec.x, t / vec.y};
    }
} //namespace core

#endif
