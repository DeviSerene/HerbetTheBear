#include "Timer.h"

Timer::Timer() : currentTime(0.0f), duration(1.0f) {}
Timer::Timer(float _duration) : currentTime(0.0f), duration(_duration) { }

void Timer::Update(float _delta) {
	currentTime += _delta;
}

void Timer::Wait(float _duration) {
	duration = _duration;
}

void Timer::Reset() {
	currentTime = 0;
}

bool Timer::Completed() {
	return currentTime >= duration;
}