//
// Created by Mat on 16.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_CORE_INCLUDE_FORVEC2_H_
#define GAME_MOTOR_ENGINE_CORE_INCLUDE_FORVEC2_H_

#include <array>
#include "vec2.h"

namespace core {
template<typename T>
struct FourVec2 {
 private:
  std::array<T, 4> x{};
  std::array<T, 4> y{};

  constexpr FourVec2() = default;
  constexpr FourVec2(std::initializer_list<vec2<T>> &other) {
    if (other.size() <= 4) {
      for (const auto &_ : other) {
        x[_] = _.x_;
        y = _.y_;
      }
    }
  };

 public:

  FourVec2(const float new_x, const float new_y) : x(new_x), y(new_y) {};

  FourVec2<T> operator+(FourVec2<T> other) const {};

};

//template<>
//FourVec2<int>::operator+(FourVec2<int> other) const {
//  return {1, 0}; //actual calculs
//};

}
#endif //GAME_MOTOR_ENGINE_CORE_INCLUDE_FORVEC2_H_
