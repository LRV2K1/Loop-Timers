#pragma once

class ISleepFunction
{
public:
	virtual ~ISleepFunction() = default;
	virtual void Sleep(const double& milliseconds) = 0;
};

class ThreadSleep : public ISleepFunction
{
public:
	virtual void Sleep(const double& milliseconds) override;
};

class LockSleep : public ISleepFunction
{
public:
	virtual void Sleep(const double& milliseconds) override;
};

class PerfectSleep : public ISleepFunction
{
public:
	virtual void Sleep(const double& milliseconds) override;
};

class RobustSleep : public ISleepFunction
{
public:
	RobustSleep(double period, double tolerance) : period(period), tolerance(tolerance) {};
	virtual void Sleep(const double& milliseconds) override;
private:
	double period;
	double tolerance;
};

