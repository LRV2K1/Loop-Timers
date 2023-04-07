#include "LoopTimers.h"
#include "SleepFunctions.h"

std::chrono::steady_clock::time_point SingleLoopTimer::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
	return loopStartTime;
}

std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> SingleLoopTimer::HandleLoop()
{
	std::chrono::steady_clock::time_point loopStartTime = this->loopStartTime;
	std::chrono::steady_clock::time_point loopEndTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::duration sleepTime = std::chrono::nanoseconds(int64_t(loopTime * 1e6)) - (loopEndTime - loopStartTime);
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
	StartLoop();
	return std::make_tuple(std::chrono::high_resolution_clock::now() - loopStartTime, this->loopStartTime);
}

std::chrono::steady_clock::time_point DoubleLoopTimer::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
	return loopStartTime;
}

std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> DoubleLoopTimer::HandleLoop()
{
	std::chrono::steady_clock::time_point loopStartTime = this->loopStartTime;
	std::chrono::steady_clock::time_point loopEndTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::duration sleepTime;
	if (overTime.count() > 0)
		sleepTime = (std::chrono::nanoseconds(int64_t(loopTime * 1e6)) - overTime) - (loopEndTime - loopStartTime);
	else
		sleepTime = (std::chrono::nanoseconds(int64_t(loopTime * 1e6))) - (loopEndTime - loopStartTime);
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
	StartLoop();
	overTime = (std::chrono::high_resolution_clock::now() - loopStartTime) - std::chrono::nanoseconds(int64_t(loopTime * 1e6));
	return std::make_tuple(std::chrono::high_resolution_clock::now() - loopStartTime, this->loopStartTime);
}

std::chrono::steady_clock::time_point AllLoopTimerC::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
	return loopStartTime;
}

std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> AllLoopTimerC::HandleLoop()
{
	std::chrono::steady_clock::time_point loopStartTime = this->loopStartTime;
	std::chrono::steady_clock::time_point loopEndTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::duration sleepTime;
	if (overTime.count() > 0)
		sleepTime = (std::chrono::nanoseconds(int64_t(loopTime * 1e6)) - overTime) - (loopEndTime - loopStartTime);
	else
		sleepTime = (std::chrono::nanoseconds(int64_t(loopTime * 1e6))) - (loopEndTime - loopStartTime);
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
	StartLoop();
	overTime += (std::chrono::high_resolution_clock::now() - loopStartTime) - std::chrono::nanoseconds(int64_t(loopTime * 1e6));
	return std::make_tuple(std::chrono::high_resolution_clock::now() - loopStartTime, this->loopStartTime);
}

std::chrono::steady_clock::time_point AllLoopTimerS::StartLoop()
{
	loopStartTime = std::chrono::high_resolution_clock::now();
	if (loopItteration == 0)
	{
		timerStartTime = loopStartTime;
	}
	loopItteration++;
	return loopStartTime;
}

std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> AllLoopTimerS::HandleLoop()
{
	std::chrono::steady_clock::time_point loopStartTime = this->loopStartTime;
	std::chrono::steady_clock::time_point endTime = (timerStartTime + std::chrono::nanoseconds(loopItteration * int64_t(loopTime * 1e6)));
	std::chrono::steady_clock::duration sleepTime = endTime - loopStartTime;
	double sleepMs = sleepTime.count() / 1e6;
	sleepFunction->Sleep(sleepMs);
	StartLoop();
	return std::make_tuple(std::chrono::high_resolution_clock::now() - loopStartTime, this->loopStartTime);
}