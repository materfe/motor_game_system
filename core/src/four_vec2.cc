//
// Created by Mat on 16.10.2024.
//

#include <numeric>
#include "four_vec2.h"
#include "common.h"

//ADD
template<>
core::FourVec2<float> core::FourVec2<float>::operator+(const FourVec2<float>& other) const {

  FourVec2<float> result;

  //load all
  __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(x.data()));
  __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(other.x.data()));
  __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(y.data()));
  __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(other.y.data()));

  //add
  __m128i x_res = _mm_add_epi32(x1, x2);
  __m128i y_res = _mm_add_epi32(y1, y2);

  //store and result
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.x.data()), x_res);
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.y.data()), y_res);

  return result;
}

//SUB
template<>
core::FourVec2<float> core::FourVec2<float>::operator-(const FourVec2<float> other) const {

  FourVec2<float> result;

  //load all
  __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(x.data()));
  __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(other.x.data()));
  __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(y.data()));
  __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(other.y.data()));

  //add
  __m128i x_res = _mm_sub_epi32(x1, x2);
  __m128i y_res = _mm_sub_epi32(y1, y2);

  //store and result
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.x.data()), x_res);
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.y.data()), y_res);

  return result;
}

//MULTI
template<>
core::FourVec2<float> core::FourVec2<float>::operator*(const float other) const {

  FourVec2<float> result;
  std::array<float, 4> scalar{other, other, other, other};


  //load all
  __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(x.data()));
  __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(y.data()));
  __m128i scalar_simd = _mm_loadu_si128(reinterpret_cast<const __m128i *>(scalar.data()));

  //add
  __m128i x_res = _mm_mullo_epi32(x1, scalar_simd);
  __m128i y_res = _mm_mullo_epi32(y1, scalar_simd);

  //store and result
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.x.data()), x_res);
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.y.data()), y_res);

  return result;
}

template<>
core::FourVec2<float> core::FourVec2<float>::operator/(const float other) const {

  FourVec2<float> result;

  std::array<float, 4> scalar{other, other, other, other};


  //load all
  __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(x.data()));
  __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(y.data()));
  __m128i scalar_simd = _mm_loadu_si128(reinterpret_cast<const __m128i *>(scalar.data()));

  //add
  __m128i x_res = _mm_div_epi32(x1, scalar_simd);
  __m128i y_res = _mm_div_epi32(y1, scalar_simd);

  //store and result
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.x.data()), x_res);
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.y.data()), y_res);

  return result;
}

template<>
float core::FourVec2<float>::DotProduct(const FourVec2<float> &other) const {

  //load all
  __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(x.data()));
  __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(y.data()));
  __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(other.x.data()));
  __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(other.y.data()));

  //mult
  __m128i product_x = _mm_mullo_epi32(x1, x2);
  __m128i product_y = _mm_mullo_epi32(y1, y2);

  //sum and store and return
  __m128i sum = _mm_add_epi32(product_x, product_y);
  std::array<int32_t, 4> result{};
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.data()), sum);

  return static_cast<float>(std::accumulate(result.begin(), result.end(), 0));
}


template<>
core::FourVec2<float> core::FourVec2<float>::Normalise()const {

  FourVec2<float> result;

  //early exit
  float mag = Magnitude();
  if (common::AproximateZeroForFloats(mag)) {
    return FourVec2<float>{};
  }

  std::array<float, 4> scalar{mag, mag, mag, mag};

  //load all
  __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(x.data()));
  __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(y.data()));
  __m128i scalar_simd = _mm_loadu_si128(reinterpret_cast<const __m128i *>(scalar.data()));

  //add
  __m128i x_res = _mm_div_epi32(x1, scalar_simd);
  __m128i y_res = _mm_div_epi32(y1, scalar_simd);

  //store and result
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.x.data()), x_res);
  _mm_storeu_si128(reinterpret_cast<__m128i *>(result.y.data()), y_res);

  return result;
}
