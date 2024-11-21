#include "EngineTime.h"
#include <Windows.h>

EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	//Cap to 60fps
	float framecap = 100.f / 60.f;
	if (elapsed_seconds.count() < framecap) {
		Sleep(framecap - elapsed_seconds.count());
		elapsed_seconds = std::chrono::system_clock::now() - sharedInstance->start;
	}

	sharedInstance->deltaTime = elapsed_seconds.count();
}
