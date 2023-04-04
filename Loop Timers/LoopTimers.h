#pragma once

#include <thread>
#include <chrono>

class ISleepFunction;

class ILoopTimer
{
public:
	ILoopTimer(double loopTime, ISleepFunction* sleepFunction) : loopTime(loopTime), sleepFunction(sleepFunction) {};
	virtual ~ILoopTimer() { delete sleepFunction; };
	virtual void StartLoop() = 0;
	virtual void HandleLoop() = 0;
protected:
	ISleepFunction* sleepFunction;
	double loopTime;
};

class SingleLoopTimer : public ILoopTimer
{
public:
	SingleLoopTimer(double loopTime, ISleepFunction* sleepFunction) : ILoopTimer(loopTime, sleepFunction) {}
	virtual void StartLoop() override;
	virtual void HandleLoop() override;
private:
	std::chrono::steady_clock::time_point loopStartTime;
};

