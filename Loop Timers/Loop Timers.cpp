// Loop Timers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <queue>
#include <string>
#include <tuple>

#include "SleepFunctions.h"
#include "LoopTimers.h"

#define PERIOD 20
#define TOLERANCE 0.02
#define ITERATIONS 1200
#define LOOPTIME 100

void WriteQueue(std::queue<std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point>> queue, std::chrono::steady_clock::time_point startTime, std::string name)
{
    std::ofstream file;
    file.open(name + ".csv");
    file << "Loop Time (ns)" << ";" << "Program Time (ns)" << std::endl;
    while (!queue.empty())
    {
        file << (std::get<0>(queue.front())).count() << ";" << (std::get<1>(queue.front()) - startTime).count() << std::endl;
        queue.pop();
    }
    file.close();
}

void LoopTimerTest(ILoopTimer* loopTimer, std::string name, double loopTime, int itterations)
{
    std::queue<std::tuple<std::chrono::steady_clock::duration, std::chrono::steady_clock::time_point>> queue;

    std::cout << "start " << name << ": " << std::endl;
    auto start = loopTimer->StartLoop();
    for (int i = 0; i < itterations; i++)
    {
        queue.push(loopTimer->HandleLoop());
    }
    auto end = std::get<1>(queue.back());
    double totalTime = (end - start).count() / 1e6;
    std::cout << "end " << name << ": " << std::endl;
    std::cout << "time " << name << ": " << totalTime << std::endl;
    std::cout << "mean " << name << ": " << totalTime / ITERATIONS << std::endl << std::endl;

    WriteQueue(queue, start, name);

    delete loopTimer;
}

int main()
{
    #pragma comment(lib, "winmm.lib") // for timeBeginPeriod
    timeBeginPeriod(PERIOD);

    LoopTimerTest(new SingleLoopTimer(LOOPTIME, new ThreadSleep), "SL_TS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new SingleLoopTimer(LOOPTIME, new LockSleep), "SL_LS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new SingleLoopTimer(LOOPTIME, new PerfectSleep), "SL_PS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new SingleLoopTimer(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE)), "SL_RS", LOOPTIME, ITERATIONS);

    LoopTimerTest(new DoubleLoopTimer(LOOPTIME, new ThreadSleep), "DL_TS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new DoubleLoopTimer(LOOPTIME, new LockSleep), "DL_LS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new DoubleLoopTimer(LOOPTIME, new PerfectSleep), "DL_PS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new DoubleLoopTimer(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE)), "DL_RS", LOOPTIME, ITERATIONS);

    LoopTimerTest(new AllLoopTimerC(LOOPTIME, new ThreadSleep), "ALC_TS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new AllLoopTimerC(LOOPTIME, new LockSleep), "ALC_LS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new AllLoopTimerC(LOOPTIME, new PerfectSleep), "ALC_PS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new AllLoopTimerC(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE)), "ALC_RS", LOOPTIME, ITERATIONS);

    LoopTimerTest(new AllLoopTimerS(LOOPTIME, new ThreadSleep), "ALS_TS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new AllLoopTimerS(LOOPTIME, new LockSleep), "ALS_LS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new AllLoopTimerS(LOOPTIME, new PerfectSleep), "ALS_PS", LOOPTIME, ITERATIONS);
    LoopTimerTest(new AllLoopTimerS(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE)), "ALS_RS", LOOPTIME, ITERATIONS);
}
