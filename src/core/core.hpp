#pragma once

#include "vec3.hpp"
#include <cstdlib>
#include <limits>

// Utility Functions
namespace utils {

inline float degreesToRadians(float degrees) { return degrees * M_PI / 180.f; }

inline Color toColor(Vec3<float> f) {
  return Color(f.x() * 255, f.y() * 255, f.z() * 255);
}

inline float random() {
  // Returns a random real in [0,1).
  return rand() / (RAND_MAX + 1.0);
}

inline float random(float min, float max) {
  // Returns a random real in [min,max).
  return min + (max - min) * random();
}

inline float clamp(float x, float min, float max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

inline Vec3f randomV() { return Vec3f(random(), random(), random()); }

inline Vec3f randomV(float min, float max) {
  return Vec3f(random(min, max), random(min, max), random(min, max));
}

inline Vec3f randomInUnitSphere() {
  while (true) {
    auto p = randomV(-1, 1);
    if (p.lengthSquared() >= 1)
      continue;
    return p;
  }
}

} // namespace utils