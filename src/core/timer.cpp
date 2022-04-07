#include "timer.hpp"

#include <iostream>

using namespace std;
using chrono::high_resolution_clock;
using Timepoint = chrono::time_point<high_resolution_clock>;
using chrono::time_point_cast;
using chrono::microseconds;

Profiler Profiler::ins;


Timer::Timer() {
  start = high_resolution_clock::now();
  name = "un named";
}

Timer::Timer(std::string _name) {
	start = high_resolution_clock::now();
  name = _name;
}

Timer::~Timer() {
  Timepoint end = high_resolution_clock::now();
	double startMics = time_point_cast<microseconds>(start).time_since_epoch().count();
	double endMics = time_point_cast<microseconds>(end).time_since_epoch().count();
	double du = (endMics - startMics) / 1000;

	Profiler::ins.data[name] = du;
}