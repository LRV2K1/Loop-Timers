// Loop Timers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

#include "SleepFunctions.h"

#define PERIOD 20
#define TOLERANCE 0.02

int main()
{
    #pragma comment(lib, "winmm.lib") // for timeBeginPeriod
    timeBeginPeriod(PERIOD);

    double totalTime = 0;
    ThreadSleep ts;
    std::cout << "start TS" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {

        ts.Sleep(100);

        auto end = std::chrono::high_resolution_clock::now();
        auto deltaNs = (end - start).count();
        double deltaMs = deltaNs / 1e6;
        totalTime += deltaMs;
        start = end;
    }
    std::cout << "end TS" << std::endl;
    std::cout << "time TS:" << totalTime / 100 << std::endl << std::endl;


    totalTime = 0;
    LockSleep ls;
    std::cout << "start LS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {

        ls.Sleep(100);

        auto end = std::chrono::high_resolution_clock::now();
        auto deltaNs = (end - start).count();
        double deltaMs = deltaNs / 1e6;
        totalTime += deltaMs;
        start = end;
    }
    std::cout << "end LS" << std::endl;
    std::cout << "time LS:" << totalTime / 100 << std::endl << std::endl;


    totalTime = 0;
    PerfectSleep ps;
    std::cout << "start PS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {

        ps.Sleep(100);

        auto end = std::chrono::high_resolution_clock::now();
        auto deltaNs = (end - start).count();
        double deltaMs = deltaNs / 1e6;
        totalTime += deltaMs;
        start = end;
    }
    std::cout << "end PS" << std::endl;
    std::cout << "time PS:" << totalTime / 100 << std::endl << std::endl;


    totalTime = 0;
    RobustSleep rs(PERIOD, TOLERANCE);
    std::cout << "start RS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {

        rs.Sleep(100);

        auto end = std::chrono::high_resolution_clock::now();
        auto deltaNs = (end - start).count();
        double deltaMs = deltaNs / 1e6;
        totalTime += deltaMs;
        start = end;
    }
    std::cout << "end RS" << std::endl;
    std::cout << "time RS:" << totalTime / 100 << std::endl << std::endl;
}
