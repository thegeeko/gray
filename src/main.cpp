#include <vector>

#include "lib/vec3.hpp"
#include "renderer/renderer.hpp"
#include "window/window.hpp"

constexpr int IMAGE_WIDTH = 1280;
constexpr int IMAGE_HEIGHT = 720;

using namespace std;

void drawUi(vector<Vec3<uint8_t>>& image, uint32_t texture) {
	// generating a texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);		// This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);		// Same

	// imgui
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
	bool opened = true;
	

	renderer::startFrame();
	ImGui::Begin("image", &opened, flags);
	ImGui::Image((void*)texture, ImVec2(IMAGE_WIDTH, IMAGE_HEIGHT));
	ImGui::End();
}

void drawImage(std::vector<Vec3<uint8_t>>& image) {
	for (int i = IMAGE_HEIGHT - 1; i >= 0; i--) {
		for (int j = 0; j < IMAGE_WIDTH; j++) {
			float r = (float)(i) / IMAGE_HEIGHT;
			float g = (float)(j) / IMAGE_WIDTH;
			float b = 0.25;

			uint8_t ir = r * 255;
			uint8_t ig = g * 255;
			uint8_t ib = b * 255;

			int pos = (i * IMAGE_WIDTH) + j;

			image[pos][0] = ir;
			image[pos][1] = ig;
			image[pos][2] = ib;
		}
	}
}

int main() {
	auto win = window::init(IMAGE_WIDTH + 50, IMAGE_HEIGHT + 50);

	GLuint texture;
	glGenTextures(1, &texture);
	std::vector<Vec3<uint8_t>> image(IMAGE_WIDTH * IMAGE_HEIGHT, {102, 28, 190});

	while (!glfwWindowShouldClose(win)) {
		drawImage(image);
		drawUi(image, texture);
		renderer::render(win);
	}

	return 0;
}