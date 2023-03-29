#include "SleepFunctions.h"

#include <thread>
#include <chrono>

void ThreadSleep::Sleep(const double& milliseconds)
{
	auto nanoseconds = std::chrono::nanoseconds((int64_t)(milliseconds * 1e6));
	std::this_thread::sleep_for(nanoseconds);
}

void LockSleep::Sleep(const double& milliseconds)
{
	auto nanoseconds = std::chrono::nanoseconds((int64_t)(milliseconds * 1e6));
	auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - start < nanoseconds);
}

void PerfectSleep::Sleep(const double& milliseconds)
{
    double seconds = milliseconds / 1e3;

    static double estimate = 5e-3;
    static double mean = 5e-3;
    static double m2 = 0;
    static int64_t count = 1;

    while (seconds > estimate)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto end = std::chrono::high_resolution_clock::now();

        double observed = (end - start).count() / 1e9;
        seconds -= observed;

        ++count;
        double delta = observed - mean;
        mean += delta / count;
        m2 += delta * (observed - mean);
        double stddev = sqrt(m2 / (count - 1));
        estimate = mean + stddev;
    }

    // spin lock
    auto start = std::chrono::high_resolution_clock::now();
    auto spinNs = int64_t(seconds * 1e9);
    auto delay = std::chrono::nanoseconds(spinNs);
    while (std::chrono::high_resolution_clock::now() - start < delay);
}

void RobustSleep::Sleep(const double& milliseconds)
{
    double seconds = milliseconds / 1e3;

    auto t0 = std::chrono::high_resolution_clock::now();
    auto target = t0 + std::chrono::nanoseconds(int64_t(seconds * 1e9));

    // sleep
    double ms = seconds * 1000 - (period + tolerance);
    int ticks = (int)(ms / period);
    if (ticks > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds((int64_t)(ticks * period)));

    // spin
    while (std::chrono::high_resolution_clock::now() < target);
}