#pragma once

#include <thread>
#include <chrono>
#include <tuple>

class ISleepFunction;

class ILoopTimer
{
public:
	ILoopTimer(double loopTime, ISleepFunction* sleepFunction) : loopTime(loopTime), sleepFunction(sleepFunction) {};
	virtual ~ILoopTimer() { delete sleepFunction; };
	virtual std::chrono::steady_clock::time_point StartLoop() = 0;
	virtual std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> HandleLoop() = 0;
protected:
	ISleepFunction* sleepFunction;
	double loopTime;
};

class SingleLoopTimer : public ILoopTimer
{
public:
	SingleLoopTimer(double loopTime, ISleepFunction* sleepFunction) : ILoopTimer(loopTime, sleepFunction) {}
	virtual std::chrono::steady_clock::time_point StartLoop() override;
	virtual std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> HandleLoop() override;
private:
	std::chrono::steady_clock::time_point loopStartTime;
};

class DoubleLoopTimer : public ILoopTimer
{
public:
	DoubleLoopTimer(double loopTime, ISleepFunction* sleepFunction) : ILoopTimer(loopTime, sleepFunction) {}
	virtual std::chrono::steady_clock::time_point StartLoop() override;
	virtual std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> HandleLoop() override;
private:
	std::chrono::steady_clock::time_point loopStartTime;
	std::chrono::steady_clock::duration overTime{ 0 };
};

class AllLoopTimerC : public ILoopTimer
{
public:
	AllLoopTimerC(double loopTime, ISleepFunction* sleepFunction) : ILoopTimer(loopTime, sleepFunction) {}
	virtual std::chrono::steady_clock::time_point StartLoop() override;
	virtual std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> HandleLoop() override;
private:
	std::chrono::steady_clock::time_point loopStartTime;
	std::chrono::steady_clock::duration overTime{ 0 };
};

class AllLoopTimerS : public ILoopTimer
{
public:
	AllLoopTimerS(double loopTime, ISleepFunction* sleepFunction) : ILoopTimer(loopTime, sleepFunction) {}
	virtual std::chrono::steady_clock::time_point StartLoop() override;
	virtual std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point> HandleLoop() override;
private:
	std::chrono::steady_clock::time_point loopStartTime;
	std::chrono::steady_clock::time_point timerStartTime;
	unsigned long long loopItteration{0};
};

