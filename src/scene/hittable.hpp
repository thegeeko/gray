#pragma once

#include "core/ray.hpp"
#include "core/vec3.hpp"

struct HitRecord {
  Point3 p;
  Vec3f normal;
  double t;
  bool frontFace;

  inline void setFaceNormal(const Ray &r, const Vec3f &outward_normal) {
    frontFace = dot(r.direction(), outward_normal) < 0;
    normal = frontFace ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  virtual bool hit(const Ray &r, double t_min, double t_max,
                   HitRecord &rec) const = 0;
};