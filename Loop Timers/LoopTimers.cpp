#include "LoopTimers.h"
#include "SleepFunctions.h"

void SingleLoopTimer::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
}

std::chrono::steady_clock::duration SingleLoopTimer::HandleLoop()
{
	std::chrono::steady_clock::time_point loopEndTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::duration sleepTime = std::chrono::nanoseconds(int64_t(loopTime * 1e6)) - (loopEndTime - loopStartTime);
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
	return std::chrono::high_resolution_clock::now() - loopStartTime;
}

void DoubleLoopTimer::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
}

std::chrono::steady_clock::duration DoubleLoopTimer::HandleLoop()
{
	std::chrono::steady_clock::time_point loopEndTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::duration sleepTime;
	if (overTime.count() > 0)
		sleepTime = (std::chrono::nanoseconds(int64_t(loopTime * 1e6)) - overTime) - (loopEndTime - loopStartTime);
	else
		sleepTime = (std::chrono::nanoseconds(int64_t(loopTime * 1e6))) - (loopEndTime - loopStartTime);
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
	overTime = (std::chrono::high_resolution_clock::now() - loopStartTime) - std::chrono::nanoseconds(int64_t(loopTime * 1e6));
	return std::chrono::high_resolution_clock::now() - loopStartTime;
}

void AllLoopTimerC::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
}

std::chrono::steady_clock::duration AllLoopTimerC::HandleLoop()
{
	std::chrono::steady_clock::time_point loopEndTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::duration sleepTime;
	if (overTime.count() > 0)
		sleepTime = (std::chrono::nanoseconds(int64_t(loopTime * 1e6)) - overTime) - (loopEndTime - loopStartTime);
	else
		sleepTime = (std::chrono::nanoseconds(int64_t(loopTime * 1e6))) - (loopEndTime - loopStartTime);
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
	overTime += (std::chrono::high_resolution_clock::now() - loopStartTime) - std::chrono::nanoseconds(int64_t(loopTime * 1e6));
	return std::chrono::high_resolution_clock::now() - loopStartTime;
}

void AllLoopTimerS::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
	if (loopItteration == 0)
	{
		timerStartTime = loopStartTime;
	}
	loopItteration++;
}

std::chrono::steady_clock::duration AllLoopTimerS::HandleLoop()
{
	std::chrono::steady_clock::time_point endTime = (timerStartTime + std::chrono::nanoseconds(loopItteration * int64_t(loopTime * 1e6)));
	std::chrono::steady_clock::duration sleepTime = endTime - loopStartTime;
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
	return std::chrono::high_resolution_clock::now() - loopStartTime;
}