//
// Created by Mat on 07.10.2024.
//

#ifndef MATRIX4_H
#define MATRIX4_H

#include "vec4.h"
#include "matrix3.h"
#include <array>

namespace core {
    template<typename T>
    class Matrix4 {
    private:
        // Four column array
        std::array<Vec4<T>, 4> columns_;

    public:
        // Constructor with initialization (element-wise)
        Matrix4(T a, T b, T c, T d,
                T e, T f, T g, T h,
                T i, T j, T k, T l,
                T m, T n, T o, T p) {
            columns_[0] = Vec4<T>(a, b, c, d);
            columns_[1] = Vec4<T>(e, f, g, h);
            columns_[2] = Vec4<T>(i, j, k, l);
            columns_[3] = Vec4<T>(m, n, o, p);
        }

        Matrix4(const Vec4<T> &v, const Vec4<T> &w, const Vec4<T> &c, const Vec4<T> &d) {
            columns_[0] = v;
            columns_[1] = w;
            columns_[2] = c;
            columns_[3] = d;
        }

        explicit Matrix4(const std::array<Vec4<T>, 4> &v) {
            columns_ = v;
        }

        Matrix4(std::initializer_list<Vec4<T> > &init) {
            columns_[0] = init[0];
            columns_[1] = init[1];
            columns_[2] = init[2];
            columns_[3] = init[3];
        }

        //identity
        [[nodiscard]] static constexpr Matrix4<T> Identity() {
            return Matrix4<T>(Vec4<T>(1, 0, 0, 0), Vec4<T>(0, 1, 0, 0), Vec4<T>(0, 0, 1, 0), Vec4<T>(0, 0, 0, 1));
        }

        //get columns
        [[nodiscard]] constexpr Vec4<T> GetFirstColumn() const {
            return columns_[0];
        }

        [[nodiscard]] constexpr Vec4<T> GetSecondColumn() const {
            return columns_[1];
        }

        [[nodiscard]] constexpr Vec4<T> GetThirdColumn() const {
            return columns_[2];
        }

        [[nodiscard]] constexpr Vec4<T> GetFourthColumn() const {
            return columns_[3];
        }

        // Matrix addition
        constexpr Matrix4<T> operator+(const Matrix4<T> &other) const {
            return Matrix4<T>(
                columns_[0] + other.columns_[0],
                columns_[1] + other.columns_[1],
                columns_[2] + other.columns_[2],
                columns_[3] + other.columns_[3]
            );
        }

        // Matrix subtraction
        constexpr Matrix4<T> operator-(const Matrix4<T> &other) const {
            return Matrix4<T>(
                columns_[0] - other.columns_[0],
                columns_[1] - other.columns_[1],
                columns_[2] - other.columns_[2],
                columns_[3] - other.columns_[3]
            );
        }

        //i stands for the column number and j for the element number
        constexpr T operator()(const int i, const int j) const {
            if (j < 0 || j >= 4 || i < 0 || i >= 4) {
                std::terminate();
            }

            switch (i) {
                case 0:
                    return columns_[0][j];
                    break;
                case 1:
                    return columns_[1][j];
                    break;
                case 2:
                    return columns_[2][j];
                    break;
                case 3:
                    return columns_[3][j];
                    break;
                default:
                    std::terminate();
            }
        }


        // Matrix multiplication
        constexpr Matrix4<T> operator*(const Matrix4<T> &other) const {
            Matrix4<T> result = Identity();

            // Iterate over each column of the result matrix
            for (int j = 0; j < 4; ++j) {
                result.columns_[j] = Vec4<T>(
                    columns_[0].x * other.columns_[j].x + columns_[1].x * other.columns_[j].y + columns_[2].x * other.
                    columns_[j].z + columns_[3].x * other.columns_[j].w, // First row
                    columns_[0].y * other.columns_[j].x + columns_[1].y * other.columns_[j].y + columns_[2].y * other.
                    columns_[j].z + columns_[3].y * other.columns_[j].w, // Second row
                    columns_[0].z * other.columns_[j].x + columns_[1].z * other.columns_[j].y + columns_[2].z * other.
                    columns_[j].z + columns_[3].z * other.columns_[j].w, // Third row
                    columns_[0].w * other.columns_[j].x + columns_[1].w * other.columns_[j].y + columns_[2].w * other.
                    columns_[j].z + columns_[3].w * other.columns_[j].w // Fourth row
                );
            }
            return result;
        }

        // Scalar multiplication
        constexpr Matrix4<T> operator*(T scalar) const {
            return Matrix4<T>(columns_[0] * scalar, columns_[1] * scalar, columns_[2] * scalar, columns_[3] * scalar);
        }

        // Determinant of the matrix (Laplace expansion for a 4x4 matrix)
        T determinant() const {
            // Minor matrices (Matrix3) calculated for cofactor expansion along the first row
            Matrix3<T> minor0(columns_[1].y, columns_[1].z, columns_[1].w,
                              columns_[2].y, columns_[2].z, columns_[2].w,
                              columns_[3].y, columns_[3].z, columns_[3].w);

            Matrix3<T> minor1(columns_[0].y, columns_[0].z, columns_[0].w,
                              columns_[2].y, columns_[2].z, columns_[2].w,
                              columns_[3].y, columns_[3].z, columns_[3].w);

            Matrix3<T> minor2(columns_[0].y, columns_[0].z, columns_[0].w,
                              columns_[1].y, columns_[1].z, columns_[1].w,
                              columns_[3].y, columns_[3].z, columns_[3].w);

            Matrix3<T> minor3(columns_[0].y, columns_[0].z, columns_[0].w,
                              columns_[1].y, columns_[1].z, columns_[1].w,
                              columns_[2].y, columns_[2].z, columns_[2].w);

            // Calculate determinant using cofactor expansion along the first row
            return columns_[0].x * minor0.determinant()
                   - columns_[1].x * minor1.determinant()
                   + columns_[2].x * minor2.determinant()
                   - columns_[3].x * minor3.determinant();
        }
    };
}
#endif //MATRIX4_H
