#pragma once

#define GL_GLEXT_PROTOTYPES

#include <vector>

#include "GLFW/glfw3.h"
#include "lib/vec3.hpp"

namespace renderer {
	void startFrame();
	void render(GLFWwindow* win);
}		 // namespace renderer