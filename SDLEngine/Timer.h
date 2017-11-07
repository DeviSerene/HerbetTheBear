#pragma once
class Timer
{
private:
	float currentTime;
	float duration;
public:
	Timer();
	Timer(float _duration);
	void Update(float _delta);
	void Wait(float _duration);
	void Reset();
	bool Completed();
};

