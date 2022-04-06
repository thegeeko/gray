#pragma once

#include "lib/vec3.hpp"

class ray {
public:
	ray() {}
	ray(const Vec3<float>& origin, const Vec3<float>& direction):
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