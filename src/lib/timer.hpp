#pragma once

#include <chrono>
#include <string>
#include <unordered_map>

#include "imgui.h"

struct Timer {
  Timer();
  Timer(std::string name);
  ~Timer();

private:
  std::string name;
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

class Profiler {
public:
  static void draw() {
    ins.mDraw();
  }

private:
  Profiler() = default;
  std::unordered_map<std::string, double> data;
  static Profiler ins;

  void mDraw() {
    ImGui::Begin("Profiler");
    for (auto &[name, time] : data) {
      ImGui::Text("%s took %lf", name.c_str(), time);
    }
    ImGui::End();
  };
  void mClear() { data.clear(); }

  friend Timer;
};