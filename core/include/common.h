#ifndef common_h
#define common_h
#include <cstdlib>
#include <random>
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif


inline std::random_device r;
inline std::default_random_engine e1(r());

namespace common {
#define EPSILON 2.2204460492503131e-016f
#define PI 3.14159265358979323846f

//will compare your value - your target to epsilon -> if lower -> return true
inline bool AproximateZeroForFloats(const float value) {
  if (abs(value - 0.0f) < EPSILON) {
    return true;
  }
  return false;
}

//give a pixel size, and it will become a meter (100 pixels = 1m)
inline float ToMeters(const float &value) {
  return value / 100.0f;
}
//give a meter size, and it will return a pixel size using (100 pixels = 1m)
inline float ToPixels(const float &value) {
  return value * 100.0f;
}

//input a radian value and it returns a degree value
inline float ToDegree(const float &rad_value) {
  return rad_value * 180 / PI;
}
//input a degree value and it returns a radian
inline float ToRadians(const float &degrees_value) {
  return degrees_value * PI / 180;
}

inline int GenerateANumber(const int limit) {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
  std::uniform_int_distribution<int> uniform_dist(0, limit);
  return uniform_dist(e1);
}

}

#endif
