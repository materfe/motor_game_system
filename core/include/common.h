#ifndef common_h
#define common_h
#include <cstdlib>
#include <random>
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif




namespace common {
#define EPSILON 2.2204460492503131e-016f
#define PI 3.14159265358979323846f

//will compare your value - your target to epsilon -> if lower -> return true
static bool AproximateZeroForFloats(const float value) {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  if (abs(value - 0.0f) < EPSILON) {
    return true;
  }
  return false;
}

//give a pixel size, and it will become a meter (100 pixels = 1m)
constexpr float ToMeters(const float &value) {
  return value / 100.0f;
}
//give a meter size, and it will return a pixel size using (100 pixels = 1m)
constexpr float ToPixels(const float &value) {
  return value * 100.0f;
}

//input a radian value and it returns a degree value
constexpr float ToDegree(const float &rad_value) {
  return rad_value * 180 / PI;
}
//input a degree value and it returns a radian
constexpr float ToRadians(const float &degrees_value) {
  return degrees_value * PI / 180;
}

template<typename T>
T GenerateRandomNumber(T min_number, T max_number)
{
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "function requires a number"); //compiler error if not number

  static std::random_device r;
  static std::default_random_engine e1(r()); //static -> one instance

  if constexpr (std::is_integral_v<T>)
  {
    std::uniform_int_distribution<T> uniform_dist(min_number, max_number);
    return uniform_dist(e1);
  }
  else if constexpr (std::is_floating_point_v<T>)
  {
    std::uniform_real_distribution<T> dist(min_number, max_number);
    return dist(e1);
  }
}
}

#endif
