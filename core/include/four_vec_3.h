//
// Created by Mat on 16.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_CORE_INCLUDE_FOUR_VEC_3_H_
#define GAME_MOTOR_ENGINE_CORE_INCLUDE_FOUR_VEC_3_H_

#include <cmath>
#include <array>
#include "vec3.h"

namespace core {
template<typename T>
struct FourVec3 {
 private:
  std::array<T, 4> x;
  std::array<T, 4> y;
  std::array<T, 4> z;

 public:
  // Constructors and operators
  FourVec3() = default;
  FourVec3(std::initializer_list<Vec3<T>> &other) {
    auto it = other.begin();
    for (size_t i = 0; i < 4 && it != other.end(); ++i, ++it) {
      x[i] = it->x;
      y[i] = it->y;
      z[i] = it->z;
    }
  };
  FourVec3(std::array<T, 4>& other_x, std::array<T, 4>& other_y, std::array<T, 4>& other_z)
  {
    for(int i = 0; i < 4; i++)
    {
      x[i] = other_x[i];
      y[i] = other_y[i];
      z[i] = other_z[i];
    }
  }

  FourVec3 operator+(const FourVec3 &other) const;
  FourVec3 operator-(const FourVec3 &other) const;
  FourVec3 operator*(T scalar) const;
  FourVec3 operator/(T scalar) const;

  std::array<T, 4> DotProduct(const FourVec3 &other) const;
  std::array<T, 4> SqrtMagnitude() const;
  std::array<T, 4> Magnitude() const;
  FourVec3 Normalise() const;
  static FourVec3 Cross(FourVec3& v1, FourVec3& v2);


  [[nodiscard]] std::array<T, 4> GetX() const {return x;}
  [[nodiscard]] std::array<T, 4> GetY() const {return y;}
  [[nodiscard]] std::array<T, 4> GetZ() const {return z;}
};
}
#endif //GAME_MOTOR_ENGINE_CORE_INCLUDE_FOUR_VEC_3_H_
