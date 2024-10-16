//
// Created by Mat on 07.10.2024.
//

#ifndef MATRIX2_H
#define MATRIX2_H

#include <array>
#include "vec2.h"
namespace core {
    template <typename T>
    struct Matrix2 {
    private:
        // Two column array
        std::array<Vec2<T>, 2> columns_;

    public:
        // Constructor with initialization
        Matrix2(T a, T b, T c, T d) {
            columns_[0] = Vec2<T>(a, b);
            columns_[1] = Vec2<T>(c, d);
        }
        Matrix2(const Vec2<T>& col1, const Vec2<T>& col2) {
            columns_[0] = col1;
            columns_[1] = col2;
        }
        explicit Matrix2(const std::array<Vec2<T>, 2>& cols) {
            columns_ = cols;
        }
        Matrix2(std::initializer_list<Vec2<T>>& init) {
            columns_[0] = init[0];
            columns_[1] = init[1];
        }

        //return a selected colum
        [[nodiscard]] constexpr Vec2<T> GetFirstColumn() const {
            return columns_[0];
        }
        [[nodiscard]] constexpr Vec2<T> GetSecondColumn() const {
            return columns_[1];
        }

        //identity
        [[nodiscard]] static constexpr Matrix2<T> Identity() {
            return Matrix2<T>(1, 0, 0, 1);
        }

        // Matrix addition
        constexpr Matrix2<T> operator+(const Matrix2<T>& other) const {
            return Matrix2<T>(columns_[0] + other.columns_[0], columns_[1] + other.columns_[1]);
        }

        // Matrix subtraction
        constexpr Matrix2<T> operator-(const Matrix2<T>& other) const {
            return Matrix2<T>(columns_[0] - other.columns_[0], columns_[1] - other.columns_[1]);
        }

        // Matrix multiplication: C = A * B
        constexpr Matrix2<T> operator*(const Matrix2<T>& other) const {
            //returned matrix
            Matrix2<T> result = Identity();

            // Iterate over each column of the result
            for (int j = 0; j < 2; ++j) {
                // Each column in the result is a linear combination of the columns of A
                result.columns_[j] = Vec2<T>(
                    columns_[0].x_ * other.columns_[j].x_ + columns_[1].x_ * other.columns_[j].y_, // First row
                    columns_[0].y_ * other.columns_[j].x_ + columns_[1].y_ * other.columns_[j].y_ // Second row
                );
            }

            return result;
        }

        // Scalar multiplication
        constexpr Matrix2<T> operator*(T scalar) const {
            return Matrix2<T>(columns_[0] * scalar, columns_[1] * scalar);
        }

        //i stands for the column number and j for the element number
        constexpr T operator()(const int i, const int j) const {
            if (j < 0 || j >= 2 || i < 0 || i >= 2) {
                std::terminate();
            }
            return i == 0 ? columns_[0][j] : columns_[1][j];
        }


        // Determinant of the matrix
        [[nodiscard]] T Determinant() const {
            return columns_[0].x_ * columns_[1].y_ - columns_[1].x_ * columns_[0].y_;
        }

        //inverse
        //place an optionel instead of the std::terminate()
        Matrix2<T> Inverse() const {
            T det = Determinant();
            if (det == 0) {
                std::terminate();
            }
            Matrix2<T> cofactor(
                columns_[1].y_, -columns_[0].y_,
                -columns_[1].x_, columns_[0].x_
            );
            return cofactor * (1 / det);
        }
    };
    template <typename T>
    constexpr Matrix2<T> operator*(T scalar, Matrix2<T>& other) {
        return Matrix2<T>(scalar * other.columns_[0], scalar * other.columns_[1]);
    }
}

#endif //MATRIX2_H
