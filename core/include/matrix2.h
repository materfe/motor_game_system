//
// Created by Mat on 07.10.2024.
//

#ifndef MATRIX2_H
#define MATRIX2_H

#include <array>
#include "vec2.h"
namespace core {
    template <typename T>
    struct matrix2 {
    private:
        // Two column array
        std::array<vec2<T>, 2> columns_;

    public:
        // Constructor with initialization
        matrix2(T a, T b, T c, T d) {
            columns_[0] = vec2<T>(a, b);
            columns_[1] = vec2<T>(c, d);
        }
        matrix2(const vec2<T>& col1, const vec2<T>& col2) {
            columns_[0] = col1;
            columns_[1] = col2;
        }
        explicit matrix2(const std::array<vec2<T>, 2>& cols) {
            columns_ = cols;
        }
        matrix2(std::initializer_list<vec2<T>>& init) {
            columns_[0] = init[0];
            columns_[1] = init[1];
        }

        //return a selected colum
        [[nodiscard]] constexpr vec2<T> GetFirstColumn() const {
            return columns_[0];
        }
        [[nodiscard]] constexpr vec2<T> GetSecondColumn() const {
            return columns_[1];
        }

        //indentity
        [[nodiscard]] static constexpr matrix2<T> Identity() {
            return matrix2<T>(1, 0, 0, 1);
        }

        // Matrix addition
        constexpr matrix2<T> operator+(const matrix2<T>& other) const {
            return matrix2<T>(columns_[0] + other.columns_[0], columns_[1] + other.columns_[1]);
        }

        // Matrix subtraction
        constexpr matrix2<T> operator-(const matrix2<T>& other) const {
            return matrix2<T>(columns_[0] - other.columns_[0], columns_[1] - other.columns_[1]);
        }

        // Matrix multiplication: C = A * B
        constexpr matrix2<T> operator*(const matrix2<T>& other) const {
            //returned matrix
            matrix2<T> result = Identity();

            // Iterate over each column of the result
            for (int j = 0; j < 2; ++j) {
                // Each column in the result is a linear combination of the columns of A
                result.columns_[j] = vec2<T>(
                    columns_[0].x_ * other.columns_[j].x_ + columns_[1].x_ * other.columns_[j].y_, // First row
                    columns_[0].y_ * other.columns_[j].x_ + columns_[1].y_ * other.columns_[j].y_ // Second row
                );
            }

            return result;
        }

        // Scalar multiplication
        constexpr matrix2<T> operator*(T scalar) const {
            return matrix2<T>(columns_[0] * scalar, columns_[1] * scalar);
        }


        // Determinant of the matrix
        [[nodiscard]] T Determinant() const {
            return columns_[0].x_ * columns_[1].y_ - columns_[1].x_ * columns_[0].y_;
        }

        //inverse
        //place an optionnel instead of the std::terminate()
        matrix2<T> Inverse() const {
            T det = Determinant();
            if (det == 0) {
                std::terminate();
            }
            matrix2<T> cofactor(
                columns_[1].y_, -columns_[0].y_,
                -columns_[1].x_, columns_[0].x_
            );
            return cofactor * (1 / det);
        }
    };
    template <typename T>
    matrix2<T> operator*(T scalar, matrix2<T>& other) {
        return matrix2<T>(scalar * other.columns_[0], scalar * other.columns_[1]);
    }
}

#endif //MATRIX2_H
