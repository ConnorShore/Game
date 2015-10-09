#pragma once

class Timing
{

public:
	Timing();
	~Timing();

	void FpsLimitInit();
	void TimeInit();
	void CalculateFPS(bool printFPS);
	void LimitFPS(const float MAX_FPS = 1000);
	void calcDeltaTime();

	const int getFPS() const { return _fpsCurrent; }
	const float getDeltaTime() const { return _deltaTime;}

private:
	unsigned int _initTick, _fpsLastTime, _fpsCurrent, _fpsFrames;
	float _deltaTime;
};
