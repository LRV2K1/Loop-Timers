// Loop Timers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <queue>
#include <string>

#include "SleepFunctions.h"
#include "LoopTimers.h"

#define PERIOD 20
#define TOLERANCE 0.02
#define ITTERATIONS 10000
#define LOOPTIME 100

void WriteQueue(std::queue<std::chrono::steady_clock::duration> queue, std::string name)
{
    std::ofstream file;
    file.open(name + ".csv");
    file << "Loop Time (ns)" << std::endl;
    while (!queue.empty())
    {
        file << (queue.front()).count() << std::endl;
        queue.pop();
    }
    file.close();
}

void LoopTimerTest(ILoopTimer* loopTimer, std::string name, double loopTime, int itterations)
{
    std::queue<std::chrono::steady_clock::duration> queue;

    std::cout << "start " << name << ": " << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < itterations; i++)
    {
        loopTimer->StartLoop();
        queue.push(loopTimer->HandleLoop());
    }
    auto end = std::chrono::high_resolution_clock::now();
    double totalTime = (end - start).count() / 1e6;
    std::cout << "end " << name << ": " << std::endl;
    std::cout << "time " << name << ": " << totalTime / ITTERATIONS << std::endl << std::endl;

    WriteQueue(queue, name);

    delete loopTimer;
}

int main()
{
    #pragma comment(lib, "winmm.lib") // for timeBeginPeriod
    timeBeginPeriod(PERIOD);

    LoopTimerTest(new SingleLoopTimer(LOOPTIME, new ThreadSleep), "SL_TS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new SingleLoopTimer(LOOPTIME, new LockSleep), "SL_LS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new SingleLoopTimer(LOOPTIME, new PerfectSleep), "SL_PS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new SingleLoopTimer(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE)), "SL_RS", LOOPTIME, ITTERATIONS);

    LoopTimerTest(new DoubleLoopTimer(LOOPTIME, new ThreadSleep), "DL_TS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new DoubleLoopTimer(LOOPTIME, new LockSleep), "DL_LS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new DoubleLoopTimer(LOOPTIME, new PerfectSleep), "DL_PS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new DoubleLoopTimer(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE)), "SL_RS", LOOPTIME, ITTERATIONS);

    LoopTimerTest(new AllLoopTimerC(LOOPTIME, new ThreadSleep), "ALC_TS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new AllLoopTimerC(LOOPTIME, new LockSleep), "ALC_LS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new AllLoopTimerC(LOOPTIME, new PerfectSleep), "ALC_PS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new AllLoopTimerC(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE)), "ALC_RS", LOOPTIME, ITTERATIONS);

    LoopTimerTest(new AllLoopTimerS(LOOPTIME, new ThreadSleep), "ALS_TS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new AllLoopTimerS(LOOPTIME, new LockSleep), "ALS_LS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new AllLoopTimerS(LOOPTIME, new PerfectSleep), "ALS_PS", LOOPTIME, ITTERATIONS);
    LoopTimerTest(new AllLoopTimerS(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE)), "ALS_RS", LOOPTIME, ITTERATIONS);
}
