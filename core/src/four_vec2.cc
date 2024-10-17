//
// Created by Mat on 16.10.2024.
//

#include <numeric>
#include "four_vec2.h"
#include "common.h"
#include <exception>

//ADD
template<>
core::FourVec2<float> core::FourVec2<float>::operator+(const FourVec2<float>& other) const {

  FourVec2<float> result;

  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 x2 = _mm_loadu_ps(other.x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 y2 = _mm_loadu_ps(other.y.data());

  __m128 x_res = _mm_add_ps(x1, x2);
  __m128 y_res = _mm_add_ps(y1, y2);

  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);


  return result;
}


//SUB
template<>
core::FourVec2<float> core::FourVec2<float>::operator-(const FourVec2<float>& other) const {

  FourVec2<float> result;

  //load all
  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 x2 = _mm_loadu_ps(other.x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 y2 = _mm_loadu_ps(other.y.data());

  //add
  __m128 x_res = _mm_sub_ps(x1, x2);
  __m128 y_res = _mm_sub_ps(y1, y2);

  //store and result
  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);

  return result;
}


//MULTI
template<>
core::FourVec2<float> core::FourVec2<float>::operator*(const float other) const {

  FourVec2<float> result;
  std::array<float, 4> scalar{other, other, other, other};


  //load all
  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 scalar_simd = _mm_loadu_ps(scalar.data());

  //add
  __m128 x_res = _mm_mul_ps(x1, scalar_simd);
  __m128 y_res = _mm_mul_ps(y1, scalar_simd);

  //store and result
  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);

  return result;
}


template<>
core::FourVec2<float> core::FourVec2<float>::operator/(const float other) const {

  FourVec2<float> result;

  std::array<float, 4> scalar{other, other, other, other};

  //load all
  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 scalar_simd = _mm_loadu_ps(scalar.data());

  //add
  __m128 x_res = _mm_div_ps(x1, scalar_simd);
  __m128 y_res = _mm_div_ps(y1, scalar_simd);

  //store and result
  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);

  return result;
}


template<>
std::array<float, 4> core::FourVec2<float>::DotProduct(const FourVec2<float> &other) const {

  //load all
  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());
  __m128 x2 = _mm_loadu_ps(other.x.data());
  __m128 y2 = _mm_loadu_ps(other.y.data());

  //mult
  __m128 product_x = _mm_mul_ps(x1, x2);
  __m128 product_y = _mm_mul_ps(y1, y2);

  //sum and store and return
  __m128 sum = _mm_add_ps(product_x, product_y);
  std::array<float, 4> result{};
  _mm_storeu_ps(result.data(), sum);

  return result;
}


template <>
std::array<float, 4> core::FourVec2<float>::SqrtMagnitude() const
{
  std::array<float, 4> result{};

  // Load the x and y components
  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());

  // Square the components
  __m128 x_sq = _mm_mul_ps(x1, x1);
  __m128 y_sq = _mm_mul_ps(y1, y1);

  // Sum the squares
  __m128 square_magnitude = _mm_add_ps(x_sq, y_sq);

  // Store the result
  _mm_storeu_ps(result.data(), square_magnitude);

  return result;
}


template<>
std::array<float, 4> core::FourVec2<float>::Magnitude() const {

  // Call SquareMagnitude to get the squared magnitudes
  std::array<float, 4> squared_magnitude = SqrtMagnitude();

  // Compute the square root of each element in the squared magnitudes
  __m128 squared_magnitude_ps = _mm_loadu_ps(squared_magnitude.data());
  __m128 magnitude_ps = _mm_sqrt_ps(squared_magnitude_ps);

  // Store the result in an array
  std::array<float, 4> result{};
  _mm_storeu_ps(result.data(), magnitude_ps);

  return result;
}


template<>
core::FourVec2<float> core::FourVec2<float>::Normalise()const {
  FourVec2<float> result;

  // Call Magnitude to get the magnitudes of the vector elements
  std::array<float, 4> magnitude = Magnitude();

  // Load the x and y components
  __m128 x1 = _mm_loadu_ps(x.data());
  __m128 y1 = _mm_loadu_ps(y.data());

  // Load the magnitude values
  __m128 magnitude_ps = _mm_loadu_ps(magnitude.data());

  //if dividing by 0 -> terminate
  for(int i = 0 ; i < 4; i++)
  {
    if(common::AproximateZeroForFloats(magnitude[i]))
    {
      std::terminate();
    }
  }

  // Normalize by dividing x and y by the magnitude
  __m128 x_res = _mm_div_ps(x1, magnitude_ps);
  __m128 y_res = _mm_div_ps(y1, magnitude_ps);

  // Store the result
  _mm_storeu_ps(result.x.data(), x_res);
  _mm_storeu_ps(result.y.data(), y_res);

  return result;

  return result;
}