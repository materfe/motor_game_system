//
// Created by Mat on 16.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_CORE_INCLUDE_FOURVEC2_H_
#define GAME_MOTOR_ENGINE_CORE_INCLUDE_FOURVEC2_H_

#include <immintrin.h>
#include <cmath>
#include <array>
#include "vec2.h"

namespace core {
template<typename T>
struct FourVec2 {
 private:
  std::array<T, 4> x{};
  std::array<T, 4> y{};

 public:
  FourVec2() = default;
  FourVec2(std::initializer_list<Vec2<T>> &other) {
    auto it = other.begin();
    for (size_t i = 0; i < 4 && it != other.end(); ++i, ++it) {
      x[i] = it->x;
      y[i] = it->y;
    }
  };
  FourVec2(std::array<T, 4>& other_x, std::array<T, 4>& other_y)
  {
    for(int i = 0; i < 4; i++)
    {
      x[i] = other_x[i];
      y[i] = other_y[i];
    }
  }

  FourVec2<T> operator+(const FourVec2<T>& other) const;
  FourVec2<T> operator-(FourVec2<T> other) const;
  FourVec2<T> operator*(const T other) const;
  FourVec2<T> operator/(const T other) const;

  T DotProduct(const FourVec2<float> &other) const;
  FourVec2<T> Normalise() const;

  [[nodiscard]] inline float Magnitude() const
  {
    float sum_of_squares = DotProduct(*this);
    return static_cast<float >(std::sqrt(static_cast<double>(sum_of_squares)));
  }

  [[nodiscard]] std::array<T, 4> GetX() const {return x;}
  [[nodiscard]] std::array<T, 4> GetY() const {return y;}
};
}
#endif //GAME_MOTOR_ENGINE_CORE_INCLUDE_FOURVEC2_H_
