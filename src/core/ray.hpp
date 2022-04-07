#pragma once

#include "vec3.hpp"

class Ray {
public:
	Ray() {}
	Ray(const Vec3<float>& origin, const Vec3<float>& direction):
			orig(origin), dir(direction) {}

	Vec3<float> origin() const { return orig; }
	Vec3<float> direction() const { return dir; }

	Vec3<float> at(float t) const {
		return orig + t * dir;
	}

public:
	Vec3<float> orig;
	Vec3<float> dir;
};