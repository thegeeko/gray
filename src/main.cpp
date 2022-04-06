#include <vector>

#include "lib/ray.hpp"
#include "lib/timer.hpp"
#include "lib/vec3.hpp"
#include "renderer/renderer.hpp"
#include "window/window.hpp"

using namespace std;

constexpr float ASPECT_RATIO = 16.f / 9.f;
constexpr int IMAGE_WIDTH = 900;
constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;

Color toColor(Vec3<float> f) {
  return Color(f.x() * 255, f.y() * 255, f.z() * 255);
}

bool hitSphere(const Point3 &center, float radius, const ray &r) {
  Vec3f oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;
  return (discriminant > 0);
}

Color rayColor(const ray &r) {
  Timer _("Ray shooting ");

  Vec3<float> unitDirection = unitVector(r.direction());
  float t = 0.5 * (unitDirection.y() + 1.0);
  Vec3<float> colorInFloat =
      (1.f - t) * Vec3<float>(1.f, 1.f, 1.f) + t * Vec3<float>(0.5f, 0.7f, 1.f);
  return toColor(colorInFloat);
}

int main() {
  auto win = window::init(1920, 1080);

  float viewportHeight = 2.0;
  float viewportWidth = ASPECT_RATIO * viewportHeight;
  float focalLength = 1.0;

  Point3 origin = {0, 0, 0};
  Vec3f horizontal = Vec3f(viewportWidth, 0, 0);
  Vec3f vertical = Vec3f(0, viewportHeight, 0);
  Vec3f lowerLeftCorner =
      origin - horizontal / 2.f - vertical / 2.f - Vec3f(0, 0, focalLength);

  renderer::Texture tex{};
  tex.width = IMAGE_WIDTH;
  tex.height = IMAGE_HEIGHT;
  glGenTextures(1, &tex.texHandler);

  Color image[IMAGE_HEIGHT][IMAGE_WIDTH];

	Point3 sphereCenter(0, 0, -1);
	float sphereRadius = 0.5;

  while (!glfwWindowShouldClose(win)) {
    renderer::startFrame();
    Profiler::draw();

    ImGui::Begin("info");
    ImGui::Text("Width : %ipx", IMAGE_WIDTH);
    ImGui::Text("Height : %ipx", IMAGE_HEIGHT);
    ImGui::Text("Aspect Ratio : %f", ASPECT_RATIO);
    ImGui::Text("FPS : %f", ImGui::GetIO().Framerate);
    ImGui::End();

		ImGui::Begin("Contorles");
		ImGui::SliderFloat("Radius", &sphereRadius, 1, 0);
		ImGui::SliderFloat3("Center", &sphereCenter[0], -1, 1);
		ImGui::End();

    // ==============================
    for (int i = 0; i < IMAGE_WIDTH; i++) {
      for (int j = 0; j < IMAGE_HEIGHT; j++) {
        auto u = float(i) / (IMAGE_WIDTH - 1);
        auto v = float(j) / (IMAGE_HEIGHT - 1);

        ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);

        if (hitSphere(sphereCenter, sphereRadius, r))
          image[IMAGE_HEIGHT - j - 1][IMAGE_WIDTH - i - 1] = {255, 0, 0};
        else
          image[IMAGE_HEIGHT - j - 1][IMAGE_WIDTH - i - 1] = rayColor(r);
      }
    }
    // ==============================

    renderer::uploadToTexture((uint8_t *)image, tex);

    ImGui::Begin("image");
    ImGui::Image((void *)tex.texHandler, ImVec2(tex.width, tex.height));
    ImGui::End();

    renderer::render(win);
  }

  return 0;
}