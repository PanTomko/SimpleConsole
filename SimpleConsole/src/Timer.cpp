#include "Timer.h"

using namespace sc;

Timer::Timer() { 
	stored_time = std::chrono::steady_clock::duration::zero(); 
}

Timer::~Timer(){}

void Timer::start() {
	time_start = std::chrono::steady_clock::now();
}

void Timer::stop() {
	stored_time += std::chrono::steady_clock::now() - time_start;
}

void Timer::reset() {
	stored_time = std::chrono::steady_clock::duration::zero();
	time_start = std::chrono::steady_clock::now();
}

std::chrono::steady_clock::duration Timer::getElepasedTime() {
	return std::chrono::steady_clock::now() - time_start;
}

std::chrono::steady_clock::duration Timer::getStoredTime() {
	return stored_time;
}
