#pragma once

#define GL_GLEXT_PROTOTYPES

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace window {
  GLFWwindow* init(const int width, const int hight);
  void cleanUp();
}

static void DebugMessageCallback(
  GLenum source,
  GLenum type,
  GLuint id,
  GLenum severity,
  GLsizei length,
  const GLchar* msg,
  const void* data
);