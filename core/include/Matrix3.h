//
// Created by Mat on 07.10.2024.
//

#ifndef MATRIX3_H
#define MATRIX3_H


#include <vector>
namespace core {
    template <typename T>
    struct Matrix3 {
    private:
        // Two column vectors
        std::vector<T> col1;
        std::vector<T> col2;
        std::vector<T> col3;

    public:
        // Constructor with initialization
        Matrix3(T a, T b, T c, T d, T e, T f, T g, T h, T i)
            : col1({a, b, c}), col2({d, e, f}), col3({g, h, i}) {}

        // Get certain values of the matrix ::

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

        // Return the second column's first value
        [[nodiscard]] const T& GetXSecond() const {
            return col3[0];
        }

        // Return the second colum's second value
        [[nodiscard]] const T& GetYSecond() const {
            return col3[1];
        }

        // Return the second colum's third value
        [[nodiscard]] const T& GetZSecond() const {
            return col3[2];
        }



        // Matrix addition
        Matrix3<T> operator+(const Matrix3<T>& other) const {
            return Matrix3<T>(col1[0] + other.col1[0], col1[1] + other.col1[1], col1[2] + other.col1[2],
                              col2[0] + other.col2[0], col2[1] + other.col2[1], col2[2] + other.col2[2],
                              col3[0] + other.col3[0], col3[1] + other.col3[1], col3[2] + other.col3[2]);
        }

        // Matrix subtraction
        Matrix3<T> operator-(const Matrix3<T>& other) const {
            return Matrix3<T>(col1[0] - other.col1[0], col1[1] - other.col1[1], col1[2] - other.col1[2],
                              col2[0] - other.col2[0], col2[1] - other.col2[1], col2[2] - other.col2[2],
                              col3[0] - other.col3[0], col3[1] - other.col3[1], col3[2] - other.col3[2]);
        }

        // Matrix multiplication
        Matrix3<T> operator*(const Matrix3<T>& other) const {
            return Matrix3<T>(
            col1[0] * other.col1[0] + col2[0] * other.col1[1] + col3[0] * other.col1[2],
            col1[1] * other.col1[0] + col2[1] * other.col1[1] + col3[1] * other.col1[2],
            col1[2] * other.col1[0] + col2[2] * other.col1[1] + col3[2] * other.col1[2],

            col1[0] * other.col2[0] + col2[0] * other.col2[1] + col3[0] * other.col2[2],
            col1[1] * other.col2[0] + col2[1] * other.col2[1] + col3[1] * other.col2[2],
            col1[2] * other.col2[0] + col2[2] * other.col2[1] + col3[2] * other.col2[2],

            col1[0] * other.col3[0] + col2[0] * other.col3[1] + col3[0] * other.col3[2],
            col1[1] * other.col3[0] + col2[1] * other.col3[1] + col3[1] * other.col3[2],
            col1[2] * other.col3[0] + col2[2] * other.col3[1] + col3[2] * other.col3[2]
    );
        }

        // Scalar multiplication
        Matrix3<T> operator*(T scalar) const {
            return Matrix3<T>(col1[0] * scalar, col1[1] * scalar, col1[2] * scalar,
                              col2[0] * scalar, col2[1] * scalar, col2[2] * scalar,
                              col3[0] * scalar, col3[1] * scalar, col3[2] * scalar);
        }

        // Determinant of the matrix
        [[nodiscard]] T determinant() const {
            return col1[0] * (col2[1] * col3[2] - col2[2] * col3[1])
             - col2[0] * (col1[1] * col3[2] - col1[2] * col3[1])
             + col3[0] * (col1[1] * col2[2] - col1[2] * col2[1]);
            //first line times the determinant of sub-matrixes
        }
    };
}

#endif //MATRIX3_H
