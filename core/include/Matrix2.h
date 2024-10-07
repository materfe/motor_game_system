//
// Created by Mat on 07.10.2024.
//

#ifndef MATRIX2_H
#define MATRIX2_H

#include <vector>
namespace core {
    template <typename T>
    struct Matrix2 {
    private:
        // Two column vectors
        std::vector<T> col1;
        std::vector<T> col2;

    public:
        // Constructor with initialization
        Matrix2(T a, T b, T c, T d)
            : col1({a, b}), col2({c, d}) {}

        // Get certain values of the matrix ::

        // Return the first column's first value
        [[nodiscard]] const T& GetX() const {
            return col1[0];
        }

        // Return the first column's second value
        [[nodiscard]] const T& GetY() const {
            return col1[1];
        }

        // Return the second column's first value
        [[nodiscard]] const T& GetXPrime() const {
            return col2[0];
        }

        // Return the second colum's second value
        [[nodiscard]] const T& GetYPrime() const {
            return col2[1];
        }



        // Matrix addition
        Matrix2<T> operator+(const Matrix2<T>& other) const {
            return Matrix2<T>(col1[0] + other.col1[0], col1[1] + other.col1[1],
                              col2[0] + other.col2[0], col2[1] + other.col2[1]);
        }

        // Matrix subtraction
        Matrix2<T> operator-(const Matrix2<T>& other) const {
            return Matrix2<T>(col1[0] - other.col1[0], col1[1] - other.col1[1],
                              col2[0] - other.col2[0], col2[1] - other.col2[1]);
        }

        // Matrix multiplication
        Matrix2<T> operator*(const Matrix2<T>& other) const {
            return Matrix2<T>(
                col1[0] * other.col1[0] + col2[0] * other.col1[1],
                col1[1] * other.col1[0] + col2[1] * other.col1[1],
                col1[0] * other.col2[0] + col2[0] * other.col2[1],
                col1[1] * other.col2[0] + col2[1] * other.col2[1]
            );
        }

        // Scalar multiplication
        Matrix2<T> operator*(T scalar) const {
            return Matrix2<T>(col1[0] * scalar, col1[1] * scalar,
                              col2[0] * scalar, col2[1] * scalar);
        }

        // Determinant of the matrix
        [[nodiscard]] T determinant() const {
            return col1[0] * col2[1] - col2[0] * col1[1];
        }
    };
}

#endif //MATRIX2_H
