//
// Created by Mat on 07.10.2024.
//

#ifndef MATRIX4_H
#define MATRIX4_H

#include <vector>
#include <iostream>

namespace core {
    template <typename T>
    class Matrix4 {

    private:
        // Four column vectors, each of size 4
        std::vector<T> col1;
        std::vector<T> col2;
        std::vector<T> col3;
        std::vector<T> col4;

    public:
        // Constructor with initialization (element-wise)
        Matrix4(T a, T b, T c, T d,
                T e, T f, T g, T h,
                T i, T j, T k, T l,
                T m, T n, T o, T p)
            : col1({a, b, c, d}), col2({e, f, g, h}), col3({i, j, k, l}), col4({m, n, o, p}) {}

        // Return the first column's first value
        [[nodiscard]] const T& GetX() const {
            return col1[0];
        }

        // Return the first column's second value
        [[nodiscard]] const T& GetY() const {
            return col1[1];
        }

        // Return the first column's third value
        [[nodiscard]] const T& GetZ() const {
            return col1[2];
        }

        // Return the first column's fourth value
        [[nodiscard]] const T& GetW() const {
            return col1[3];
        }

        // Return the second column's first value
        [[nodiscard]] const T& GetXPrime() const {
            return col2[0];
        }

        // Return the second colum's second value
        [[nodiscard]] const T& GetYPrime() const {
            return col2[1];
        }

        // Return the second colum's third value
        [[nodiscard]] const T& GetZPrime() const {
            return col2[2];
        }

        // Return the second colum's fourth value
        [[nodiscard]] const T& GetWPrime() const {
            return col2[3];
        }

        // Return the third column's first value
        [[nodiscard]] const T& GetXSecond() const {
            return col3[0];
        }

        // Return the third colum's second value
        [[nodiscard]] const T& GetYSecond() const {
            return col3[1];
        }

        // Return the third colum's third value
        [[nodiscard]] const T& GetZSecond() const {
            return col3[2];
        }

        // Return the third colum's fourth value
        [[nodiscard]] const T& GetWSecond() const {
            return col3[3];
        }

        // Return the fourth colum's first value
        [[nodiscard]] const T& GetXThird() const {
            return col4[0];
        }

        // Return the fourth colum's second value
        [[nodiscard]] const T& GetYThird() const {
            return col4[1];
        }

        // Return the fourth colum's third value
        [[nodiscard]] const T& GetZThird() const {
            return col4[2];
        }

        // Return the fourth colum's fourth value
        [[nodiscard]] const T& GetWThird() const {
            return col4[3];
        }

        // Matrix addition
        Matrix4<T> operator+(const Matrix4<T>& other) const {
            return Matrix4<T>(
                col1[0] + other.col1[0], col1[1] + other.col1[1], col1[2] + other.col1[2], col1[3] + other.col1[3],
                col2[0] + other.col2[0], col2[1] + other.col2[1], col2[2] + other.col2[2], col2[3] + other.col2[3],
                col3[0] + other.col3[0], col3[1] + other.col3[1], col3[2] + other.col3[2], col3[3] + other.col3[3],
                col4[0] + other.col4[0], col4[1] + other.col4[1], col4[2] + other.col4[2], col4[3] + other.col4[3]
            );
        }

        // Matrix subtraction
        Matrix4<T> operator-(const Matrix4<T>& other) const {
            return Matrix4<T>(
                col1[0] - other.col1[0], col1[1] - other.col1[1], col1[2] - other.col1[2], col1[3] - other.col1[3],
                col2[0] - other.col2[0], col2[1] - other.col2[1], col2[2] - other.col2[2], col2[3] - other.col2[3],
                col3[0] - other.col3[0], col3[1] - other.col3[1], col3[2] - other.col3[2], col3[3] - other.col3[3],
                col4[0] - other.col4[0], col4[1] - other.col4[1], col4[2] - other.col4[2], col4[3] - other.col4[3]
            );
        }

        // Matrix multiplication
        Matrix4<T> operator*(const Matrix4<T>& other) const {
            return Matrix4<T>(
                col1[0] * other.col1[0] + col2[0] * other.col1[1] + col3[0] * other.col1[2] + col4[0] * other.col1[3],
                col1[1] * other.col1[0] + col2[1] * other.col1[1] + col3[1] * other.col1[2] + col4[1] * other.col1[3],
                col1[2] * other.col1[0] + col2[2] * other.col1[1] + col3[2] * other.col1[2] + col4[2] * other.col1[3],
                col1[3] * other.col1[0] + col2[3] * other.col1[1] + col3[3] * other.col1[2] + col4[3] * other.col1[3],

                col1[0] * other.col2[0] + col2[0] * other.col2[1] + col3[0] * other.col2[2] + col4[0] * other.col2[3],
                col1[1] * other.col2[0] + col2[1] * other.col2[1] + col3[1] * other.col2[2] + col4[1] * other.col2[3],
                col1[2] * other.col2[0] + col2[2] * other.col2[1] + col3[2] * other.col2[2] + col4[2] * other.col2[3],
                col1[3] * other.col2[0] + col2[3] * other.col2[1] + col3[3] * other.col2[2] + col4[3] * other.col2[3],

                col1[0] * other.col3[0] + col2[0] * other.col3[1] + col3[0] * other.col3[2] + col4[0] * other.col3[3],
                col1[1] * other.col3[0] + col2[1] * other.col3[1] + col3[1] * other.col3[2] + col4[1] * other.col3[3],
                col1[2] * other.col3[0] + col2[2] * other.col3[1] + col3[2] * other.col3[2] + col4[2] * other.col3[3],
                col1[3] * other.col3[0] + col2[3] * other.col3[1] + col3[3] * other.col3[2] + col4[3] * other.col3[3],

                col1[0] * other.col4[0] + col2[0] * other.col4[1] + col3[0] * other.col4[2] + col4[0] * other.col4[3],
                col1[1] * other.col4[0] + col2[1] * other.col4[1] + col3[1] * other.col4[2] + col4[1] * other.col4[3],
                col1[2] * other.col4[0] + col2[2] * other.col4[1] + col3[2] * other.col4[2] + col4[2] * other.col4[3],
                col1[3] * other.col4[0] + col2[3] * other.col4[1] + col3[3] * other.col4[2] + col4[3] * other.col4[3]
            );
        }

        // Scalar multiplication
        Matrix4<T> operator*(T scalar) const {
            return Matrix4<T>(
                col1[0] * scalar, col1[1] * scalar, col1[2] * scalar, col1[3] * scalar,
                col2[0] * scalar, col2[1] * scalar, col2[2] * scalar, col2[3] * scalar,
                col3[0] * scalar, col3[1] * scalar, col3[2] * scalar, col3[3] * scalar,
                col4[0] * scalar, col4[1] * scalar, col4[2] * scalar, col4[3] * scalar
            );
        }

        // Determinant of the matrix (Laplace expansion for a 4x4 matrix)
        T determinant() const {
            T det3x3_1 = (col2[1] * (col3[2] * col4[3] - col3[3] * col4[2])
                        - col2[2] * (col3[1] * col4[3] - col3[3] * col4[1])
                        + col2[3] * (col3[1] * col4[2] - col3[2] * col4[1]));

            T det3x3_2 = (col2[0] * (col3[2] * col4[3] - col3[3] * col4[2])
                        - col2[2] * (col3[0] * col4[3] - col3[3] * col4[0])
                        + col2[3] * (col3[0] * col4[2] - col3[2] * col4[0]));

            T det3x3_3 = (col2[0] * (col3[1] * col4[3] - col3[3] * col4[1])
                        - col2[1] * (col3[0] * col4[3] - col3[3] * col4[0])
                        + col2[3] * (col3[0] * col4[1] - col3[1] * col4[0]));

            T det3x3_4 = (col2[0] * (col3[1] * col4[2] - col3[2] * col4[1])
                        - col2[1] * (col3[0] * col4[2] - col3[2] * col4[0])
                        + col2[2] * (col3[0] * col4[1] - col3[1] * col4[0]));

            return col1[0] * det3x3_1 - col1[1] * det3x3_2 + col1[2] * det3x3_3 - col1[3] * det3x3_4;
        }
    };
}
#endif //MATRIX4_H
