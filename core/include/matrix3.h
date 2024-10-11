//
// Created by Mat on 07.10.2024.
//

#ifndef MATRIX3_H
#define MATRIX3_H

#include <array>
#include "vec3.h"

namespace core {
    template <typename T>
    struct matrix3 {
    private:
        // Three column array
        std::array<vec3<T>, 3> columns_;

    public:
        // Constructor with initialization
        matrix3(T a, T b, T c, T d, T e, T f, T g, T h, T i) {
            columns_[0] = vec3<T>(a, b, c);
            columns_[1] = vec3<T>(d, e, f);
            columns_[2] = vec3<T>(g, h, i);
        }
        matrix3(const vec3<T>& col1, const vec3<T>& col2, const vec3<T>& col3) {
            columns_[0] = col1;
            columns_[1] = col2;
            columns_[2] = col3;
        }
        explicit matrix3(std::array<vec3<T>, 3> cols) {
            columns_ = cols;
        }
        matrix3(std::initializer_list<vec3<T>>& init) {
            columns_[0] = init[0];
            columns_[1] = init[1];
            columns_[2] = init[2];
        }

        //identity
        [[nodiscard]] static constexpr matrix3<T> Identity() {
            return matrix3<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
        }

        // Get certain values of the matrix ::
        [[nodiscard]] constexpr vec3<T> GetFirstColumn() const {
            return columns_[0];
        }
        [[nodiscard]] constexpr vec3<T> GetSecondColumn() const {
            return columns_[1];
        }
        [[nodiscard]] constexpr vec3<T> GetThirdColumn() const {
            return columns_[2];
        }


        // Matrix addition
        constexpr matrix3<T> operator+(const matrix3<T>& other) const {
            return matrix3<T>(columns_[0] + other.columns_[0],
                columns_[1] + other.columns_[1],
                columns_[2] + other.columns_[2]);
        }

        // Matrix subtraction
        constexpr matrix3<T> operator-(const matrix3<T>& other) const {
            return matrix3<T>(columns_[0] - other.columns_[0],
                columns_[1] - other.columns_[1],
                columns_[2] - other.columns_[2]);
        }

        // Matrix multiplication
        constexpr matrix3<T> operator*(const matrix3<T>& other) const {

            //returned matrix
            matrix3<T> result = Identity();

            // Iterate over each column of the result
            for (int j = 0; j < 3; ++j) {
                // Each column in the result is a linear combination of the columns of A
                result.columns_[j] = vec3<T>(
                    columns_[0].x * other.columns_[j].x + columns_[1].x * other.columns_[j].y + columns_[2].x * other.columns_[j].z, // First row
                    columns_[0].y * other.columns_[j].x + columns_[1].y * other.columns_[j].y + columns_[2].y * other.columns_[j].z, // Second row
                    columns_[0].z * other.columns_[j].x + columns_[1].z * other.columns_[j].y + columns_[2].z * other.columns_[j].z  // Third row
                );
            }

            return result;
        }

        // Scalar multiplication
        constexpr matrix3<T> operator*(T scalar) const {
            return matrix3<T>(columns_[0] * scalar, columns_[1] * scalar, columns_[2] * scalar);
        }

        // Determinant of the matrix
        [[nodiscard]] T determinant() const {
            return columns_[0].x * (columns_[1].y * columns_[2].z - columns_[2].y * columns_[1].z)
            - columns_[1].x * (columns_[0].y * columns_[2].z - columns_[2].y * columns_[0].z)
            + columns_[2].x * (columns_[0].y * columns_[1].z - columns_[1].y * columns_[0].z);
        }
    };
}

#endif //MATRIX3_H
