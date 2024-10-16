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
    template<typename T>
    struct Vec2 {
        T x_ = 0, y_ = 0;

        //set zero() to set vec to zero
        static constexpr Vec2 Zero() { return Vec2{}; }


        //add system
        constexpr Vec2 operator+(Vec2 other) const {
            return {x_ + other.x_, y_ + other.y_};
        }

        //sub system
        constexpr Vec2 operator-(Vec2 other) const {
            return {x_ - other.x_, y_ - other.y_};
        }

        //negative numbers system
        constexpr Vec2 operator-() const {
            return {-x_, -y_};
        }

        //multiply
        constexpr Vec2 operator*(T scalar) const {
            return {x_ * scalar, y_ * scalar};
        }

        constexpr T operator[](const int index) const {
            if (index < 0 || index > 1) {
                std::terminate();
            }
            if (index == 0) {
                return x_;
            }
            return y_;
        }

        //divide
        constexpr Vec2 operator/(const T scalar) const {
            const int scalar_int = static_cast<int>(scalar);
            if (scalar_int == 0) {
                std::terminate();
            } else {
                return {x_ / scalar, y_ / scalar};
            }
        }

        //dot product (produit scalare) system
        static constexpr T Dot(Vec2 v1, Vec2 v2) {
            return v1.x_ * v2.x_ + v1.y_ * v2.y_;
        }

        //perpenducular
        [[nodiscard]] constexpr Vec2 Perpendicular() const //FAIRE perpendicular 2
        {
            return {-y_, x_};
        }

        //perpendicular 2
        [[nodiscard]] constexpr Vec2 Perpendicular2() const //FAIRE perpendicular 2
        {
            return {y_, -x_};
        }

        //Lerp
        [[nodiscard]] static constexpr Vec2 Lerp(Vec2 a, Vec2 b, float t) {
            return {a.x_ + (b.x_ - a.x_) * t, a.y_ + (b.y_ - a.y_) * t};
        }

        //normalise and sqr normalise your vector
        [[nodiscard]] Vec2 Normalise() const {
            const T magnitude = Magnitude();
            if (magnitude == 0) {
                std::terminate();
            }

            const T norm_x = x_ == 0 ? 0 : x_ / magnitude;
            const T norm_y = y_ == 0 ? 0 : y_ / magnitude;
            return {norm_x, norm_y};
        }


        //calculate magnitude and sqr magnitude
        [[nodiscard]] T Magnitude() const
            requires std::is_floating_point_v<T> {
            const float length = std::sqrt(x_ * x_ + y_ * y_);
            return length;
        }

        [[nodiscard]] constexpr T SqrMagnitude() const {
            const float length = x_ * x_ + y_ * y_;
            return length;
        }
    }; //struct Vec2f

    template<typename T>
    constexpr Vec2<T> operator*(const T t, const Vec2<T> &vec) {
        return {t * vec.x_, t * vec.y_};
    }

    template<typename T>
    constexpr Vec2<T> operator/(const T t, const Vec2<T> &vec) {
        if (vec.x_ == 0 || vec.y_ == 0) {
            std::terminate();
        }

        return {t / vec.x_, t / vec.y_};
    }
} //namespace core

#endif
