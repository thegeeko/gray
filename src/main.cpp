#include <vector>

#include "core/core.hpp"
#include "core/ray.hpp"
#include "core/timer.hpp"
#include "core/vec3.hpp"
#include "renderer/renderer.hpp"
#include "scene/cam.hpp"
#include "scene/scene.hpp"
#include "scene/sphere.hpp"
#include "window/window.hpp"

using namespace std;

// iamge
constexpr float ASPECT_RATIO = 16.f / 9.f;
constexpr int IMAGE_WIDTH = 1280;
constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;
int samplesPerPixel = 1;
int maxDepth = 10;

// image
Color image[IMAGE_HEIGHT][IMAGE_WIDTH];

Vec3f rayColor(const Ray &r, const Hittable &scene, int depth) {
  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    return Vec3f(0, 0, 0);

  HitRecord rec;

  if (scene.hit(r, 0, INFINITY, rec)) {
    Point3 target = rec.p + rec.normal + utils::randomInUnitSphere();
    return 0.5f * rayColor(Ray(rec.p, target - rec.p), scene, --depth);
  }

  Vec3f unitDirection = unitVector(r.direction());
  float t = 0.5 * (unitDirection.y() + 1.0);
  Vec3f colorInFloat =
      (1.f - t) * Vec3f(1.f, 1.f, 1.f) + t * Vec3f(0.5f, 0.7f, 1.f);
  return colorInFloat;
}

void shootRays(Camera* cam, Scene* scene) {
  Timer _("Shooting rays");
  for (int i = 0; i < IMAGE_WIDTH; i++) {
    for (int j = 0; j < IMAGE_HEIGHT; j++) {

      // @FIXME
      // more than one sample cause in weird colors ..
      Vec3f pixelColor(0, 0, 0);
      for (int s = 0; s < samplesPerPixel; ++s) {
        auto u = (i + utils::random()) / (IMAGE_WIDTH - 1);
        auto v = (j + utils::random()) / (IMAGE_HEIGHT - 1);
        Ray r = cam->getRay(u, v);

        // Divide the color by the number of samples and gamma-correct for
        // gamma=2.0.

        pixelColor += rayColor(r, *scene, maxDepth);
      }

      auto scale = 1.0 / samplesPerPixel;

      auto r = pixelColor.x();
      auto g = pixelColor.y();
      auto b = pixelColor.z();

      r = sqrt(scale * r);
      g = sqrt(scale * g);
      b = sqrt(scale * b);

      image[IMAGE_HEIGHT - j - 1][IMAGE_WIDTH - i - 1] =
          // converts to 0 - 255 color
          utils::toColor({r, g, b});
    }
  }
}

int main() {
  auto win = window::init(1920, 1080);

  // scene
  Scene world;
  world.addObject(make_shared<Sphere>(Point3(0, 0, -1), 0.5));      // ball
  world.addObject(make_shared<Sphere>(Point3(0, -100.5, -1), 100)); // floor

  // cam
  Camera cam(ASPECT_RATIO);

  renderer::Texture tex{};
  tex.width = IMAGE_WIDTH;
  tex.height = IMAGE_HEIGHT;
  glGenTextures(1, &tex.texHandler);

  Vec3f imageClearColor(0, 0, 0);
  bool imagePause = true;
  bool firstFrame = true;

  while (!glfwWindowShouldClose(win)) {
    renderer::startFrame();

    if (!imagePause || firstFrame) {
      shootRays(&cam, &world);
      firstFrame = false;
    }

    renderer::uploadToTexture((uint8_t *)image, tex);

    ImGui::DockSpaceOverViewport();

    Profiler::draw();
    cam.drawUi();

    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Gray Raytracer")) {
      if (ImGui::MenuItem("close window :3")) {
        glfwSetWindowShouldClose(win, 1);
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    // display information about the frame
    ImGui::Begin("Frame Info");
    ImGui::Text("Width : %ipx", IMAGE_WIDTH);
    ImGui::Text("Height : %ipx", IMAGE_HEIGHT);
    ImGui::Text("Aspect Ratio : %f", ASPECT_RATIO);
    ImGui::Text("Samples per pixel : %i", samplesPerPixel);
    ImGui::Separator();
    ImGui::Text("DT: %f ms", ImGui::GetIO().DeltaTime * 1000);
    ImGui::Text("FPS : %f", ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Begin("Image Controles");
    ImGui::Checkbox("Pause rays shooting", &imagePause);
    ImGui::SliderInt("Sampels per Pixel", &samplesPerPixel, 0, 100);
    ImGui::SliderInt("Max depth", &maxDepth, 0, 100);
    ImGui::ColorEdit3("Clear color", &imageClearColor[0]);
    if (ImGui::Button("Clear image")) {
      auto clc = utils::toColor(imageClearColor);
      for (int i = 0; i < IMAGE_WIDTH; i++) {
        for (int j = 0; j < IMAGE_HEIGHT; j++) {
          image[IMAGE_HEIGHT - j - 1][IMAGE_WIDTH - i - 1] = clc;
        }
      }
    }
    if (ImGui::Button("Shoot rays one time")) {
      shootRays(&cam, &world);
    }
    ImGui::End();

    ImGui::Begin("Image");
    ImGui::Image((void *)tex.texHandler, ImVec2(tex.width, tex.height));
    ImGui::End();

    renderer::render(win);
  }

  return 0;
}