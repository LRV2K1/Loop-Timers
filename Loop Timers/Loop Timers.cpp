// Loop Timers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

#include "SleepFunctions.h"

#define PERIOD 1
#define TOLERANCE 0.02

int main()
{
    std::cout << "Hello World!\n";

    ThreadSleep ts;

    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "start TS" << std::endl;

    ts.Sleep(1000);

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "end TS" << std::endl;
    auto deltaNs = (end - start).count();
    double deltaMs = deltaNs / 1e6;
    std::cout << "time TS:" << deltaMs << std::endl;


    LockSleep ls;

    start = std::chrono::high_resolution_clock::now();

    std::cout << "start LS" << std::endl;

    ls.Sleep(1000);

    end = std::chrono::high_resolution_clock::now();

    std::cout << "end LS" << std::endl;
    deltaNs = (end - start).count();
    deltaMs = deltaNs / 1e6;
    std::cout << "time LS:" << deltaMs << std::endl;


    PerfectSleep ps;

    start = std::chrono::high_resolution_clock::now();

    std::cout << "start PS" << std::endl;

    ps.Sleep(1000);

    end = std::chrono::high_resolution_clock::now();

    std::cout << "end PS" << std::endl;
    deltaNs = (end - start).count();
    deltaMs = deltaNs / 1e6;
    std::cout << "time PS:" << deltaMs << std::endl;

    #pragma comment(lib, "winmm.lib") // for timeBeginPeriod
    timeBeginPeriod(PERIOD);

    RobustSleep rs(PERIOD, TOLERANCE);

    start = std::chrono::high_resolution_clock::now();

    std::cout << "start RS" << std::endl;

    rs.Sleep(1000);

    end = std::chrono::high_resolution_clock::now();

    std::cout << "end RS" << std::endl;
    deltaNs = (end - start).count();
    deltaMs = deltaNs / 1e6;
    std::cout << "time RS:" << deltaMs << std::endl;
}
