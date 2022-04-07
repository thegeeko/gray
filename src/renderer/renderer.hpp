#pragma once

#define GL_GLEXT_PROTOTYPES

#include <vector>

#include "GLFW/glfw3.h"
#include "core/vec3.hpp"

namespace renderer {

	struct Texture {
		uint32_t texHandler;
		uint32_t width;
		uint32_t height;
	};

	void startFrame();
	void render(GLFWwindow* win);

	void uploadToTexture(uint8_t* image, Texture texture);
}		 // namespace renderer