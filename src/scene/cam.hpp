#pragma once

#include "core/ray.hpp"
#include "core/vec3.hpp"
#include "imgui.h"

class Camera {
public:
  Camera(float asr) {
    float viewportHeight = 2.0;
    float viewportWidth = asr * viewportHeight;
    float focalLength = 1.0;

    origin = {0, 0, 0};
    horizontal = Vec3f(viewportWidth, 0, 0);
    vertical = Vec3f(0, viewportHeight, 0);
    lowerLeftCorner =
        origin - horizontal / 2.f - vertical / 2.f - Vec3f(0, 0, focalLength);
  }

  Ray getRay(float u, float v) const {
    return Ray(origin,
               lowerLeftCorner + u * horizontal + v * vertical - origin);
  }

	void drawUi() {
		ImGui::Begin("Camera");
		ImGui::SliderFloat3("origin", &origin[0], -1, 1);
		ImGui::End();
	}

private:
  Point3 origin;
  Point3 lowerLeftCorner;
  Vec3f horizontal;
  Vec3f vertical;
};