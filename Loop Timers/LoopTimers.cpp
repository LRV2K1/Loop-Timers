#include "LoopTimers.h"
#include "SleepFunctions.h"

void SingleLoopTimer::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
}
#include <iostream>
void SingleLoopTimer::HandleLoop()
{
	auto loopEndTime = std::chrono::high_resolution_clock::now();
	auto sleepTime = std::chrono::nanoseconds(int64_t(loopTime * 1e6)) - (loopEndTime - loopStartTime);
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
}