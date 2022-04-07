#pragma once

#include "hittable.hpp"
#include <memory>
#include <vector>

class Scene : public Hittable {
public:
  void addObject(std::shared_ptr<Hittable> obj) { gameObjects.push_back(obj); }

  bool hit(const Ray &r, double t_min, double t_max,
           HitRecord &rec) const override {

    HitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = t_max;

    for (const auto &object : gameObjects) {
      if (object->hit(r, t_min, closestSoFar, tempRec)) {
        hitAnything = true;
        closestSoFar = tempRec.t;
        rec = tempRec;
      }
    }

    return hitAnything;
  }

private:
  std::vector<std::shared_ptr<Hittable>> gameObjects;
};