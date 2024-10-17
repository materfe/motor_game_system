//
// Created by Mat on 16.10.2024.
//

#include "four_vec_3.h"
#include <immintrin.h>
#include <numeric>
#include <exception>
#include "common.h"

template<>
core::FourVec3<float> core::FourVec3<float>::operator+(const core::FourVec3<float> &other) const {
  core::FourVec3<float> result{};

  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 x2 = _mm_loadu_ps(other.x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 y2 = _mm_loadu_ps(other.y.data());
  __m128 z1 = _mm_loadu_ps(z.data());
  __m128 z2 = _mm_loadu_ps(other.z.data());

  __m128 x_res = _mm_add_ps(x1, x2);
  __m128 y_res = _mm_add_ps(y1, y2);
  __m128 z_res = _mm_add_ps(z1, z2);

  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);
  _mm_storeu_ps(result.z.data(), z_res);

  return result;
}

template<>
core::FourVec3<float> core::FourVec3<float>::operator-(const core::FourVec3<float> &other) const {
  FourVec3<float> result{};

  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 x2 = _mm_loadu_ps(other.x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 y2 = _mm_loadu_ps(other.y.data());
  __m128 z1 = _mm_loadu_ps(z.data());
  __m128 z2 = _mm_loadu_ps(other.z.data());

  __m128 x_res = _mm_sub_ps(x1, x2);
  __m128 y_res = _mm_sub_ps(y1, y2);
  __m128 z_res = _mm_sub_ps(z1, z2);

  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);
  _mm_storeu_ps(result.z.data(), z_res);

  return result;
}

template<>
core::FourVec3<float> core::FourVec3<float>::operator*(const float scalar) const {
  FourVec3<float> result{};
  std::array<float, 4> scalar_arr{scalar, scalar, scalar, scalar};

  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 z1 = _mm_loadu_ps(z.data());
  __m128 scalar_simd = _mm_loadu_ps(scalar_arr.data());

  __m128 x_res = _mm_mul_ps(x1, scalar_simd);
  __m128 y_res = _mm_mul_ps(y1, scalar_simd);
  __m128 z_res = _mm_mul_ps(z1, scalar_simd);

  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);
  _mm_storeu_ps(result.z.data(), z_res);

  return result;
}


template<>
core::FourVec3<float> core::FourVec3<float>::operator/(const float scalar) const {
  FourVec3<float> result{};
  std::array<float, 4> scalar_arr{scalar, scalar, scalar, scalar};

  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 z1 = _mm_loadu_ps(z.data());
  __m128 scalar_simd = _mm_loadu_ps(scalar_arr.data());

  __m128 x_res = _mm_div_ps(x1, scalar_simd);
  __m128 y_res = _mm_div_ps(y1, scalar_simd);
  __m128 z_res = _mm_div_ps(z1, scalar_simd);

  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);
  _mm_storeu_ps(result.z.data(), z_res);

  return result;
}


template<>
std::array<float, 4> core::FourVec3<float>::DotProduct(const core::FourVec3<float> &other) const {
  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 z1 = _mm_loadu_ps(z.data());
  __m128 x2 = _mm_loadu_ps(other.x.data());
  __m128 y2 = _mm_loadu_ps(other.y.data());
  __m128 z2 = _mm_loadu_ps(other.z.data());

  __m128 product_x = _mm_mul_ps(x1, x2);
  __m128 product_y = _mm_mul_ps(y1, y2);
  __m128 product_z = _mm_mul_ps(z1, z2);

  __m128 sum_xy = _mm_add_ps(product_x, product_y);
  __m128 dot_product = _mm_add_ps(sum_xy, product_z);

  std::array<float, 4> result{};
  _mm_storeu_ps(result.data(), dot_product);

  return result;
}


template<>
std::array<float, 4> core::FourVec3<float>::SqrtMagnitude() const {
  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 z1 = _mm_loadu_ps(z.data());

  __m128 x_sq = _mm_mul_ps(x1, x1);
  __m128 y_sq = _mm_mul_ps(y1, y1);
  __m128 z_sq = _mm_mul_ps(z1, z1);

  __m128 sq_magnitude = _mm_add_ps(_mm_add_ps(x_sq, y_sq), z_sq);

  std::array<float, 4> result{};
  _mm_storeu_ps(result.data(), sq_magnitude);

  return result;
}


template<>
std::array<float, 4> core::FourVec3<float>::Magnitude() const {
  std::array<float, 4> squared_magnitude = SqrtMagnitude();

  __m128 sq_mag_ps = _mm_loadu_ps(squared_magnitude.data());
  __m128 magnitude_ps = _mm_sqrt_ps(sq_mag_ps);

  std::array<float, 4> result{};
  _mm_storeu_ps(result.data(), magnitude_ps);

  return result;
}


template<>
core::FourVec3<float> core::FourVec3<float>::Normalise() const {
  FourVec3<float> result{};
  std::array<float, 4> magnitude = Magnitude();

  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 z1 = _mm_loadu_ps(z.data());
  __m128 magnitude_ps = _mm_loadu_ps(magnitude.data());

  for (int i = 0; i < 4; ++i) {
    if (common::AproximateZeroForFloats(magnitude[i])) {
      std::terminate();
    }
  }

  __m128 x_res = _mm_div_ps(x1, magnitude_ps);
  __m128 y_res = _mm_div_ps(y1, magnitude_ps);
  __m128 z_res = _mm_div_ps(z1, magnitude_ps);

  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);
  _mm_storeu_ps(result.z.data(), z_res);

  return result;
}


template<>
core::FourVec3<float> core::FourVec3<float>::Cross(core::FourVec3<float> &v1, core::FourVec3<float> &v2) {
//  v1.y * v2.z - v1.z * v2.y,
//      v1.z * v2.x - v1.x * v2.z,
//      v1.x * v2.y - v1.y * v2.x
  FourVec3<float> result{};

  __m128 x1 = _mm_loadu_ps(v1.x.data());
  __m128 x2 = _mm_loadu_ps(v2.x.data());
  __m128 y1 = _mm_loadu_ps(v1.y.data());
  __m128 y2 = _mm_loadu_ps(v2.y.data());
  __m128 z1 = _mm_loadu_ps(v1.z.data());
  __m128 z2 = _mm_loadu_ps(v2.z.data());

  //all mult (two by two)
  __m128 x_mult_1 = _mm_mul_ps(y1, z2);
  __m128 x_mult_2 = _mm_mul_ps(z1, y2);
  __m128 y_mult_1 = _mm_mul_ps(z1, x2);
  __m128 y_mult_2 = _mm_mul_ps(x1, z2);
  __m128 z_mult_1 = _mm_mul_ps(x1, y2);
  __m128 z_mult_2 = _mm_mul_ps(y1, x2);

  //sub the mult
  __m128 x_final = _mm_sub_ps(x_mult_1, x_mult_2);
  __m128 y_final = _mm_sub_ps(y_mult_1, y_mult_2);
  __m128 z_final = _mm_sub_ps(z_mult_1, z_mult_2);

  _mm_storeu_ps(result.x.data(), x_final);
  _mm_storeu_ps(result.y.data(), y_final);
  _mm_storeu_ps(result.z.data(), z_final);

  return result;
}