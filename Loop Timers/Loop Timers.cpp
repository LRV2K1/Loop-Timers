// Loop Timers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

#include "SleepFunctions.h"
#include "LoopTimers.h"

#define PERIOD 20
#define TOLERANCE 0.02

int main()
{
    #pragma comment(lib, "winmm.lib") // for timeBeginPeriod
    timeBeginPeriod(PERIOD);

    SingleLoopTimer SL_TS(20, new ThreadSleep);
    std::cout << "start TS" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {
        SL_TS.StartLoop();
        SL_TS.HandleLoop();
    }
    auto end = std::chrono::high_resolution_clock::now();
    double totalTime = (end - start).count() / 1e6;
    std::cout << "end TS" << std::endl;
    std::cout << "time TS:" << totalTime / 100 << std::endl << std::endl;


    SingleLoopTimer SL_LS(20, new LockSleep);
    std::cout << "start LS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {
        SL_LS.StartLoop();
        SL_LS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end LS" << std::endl;
    std::cout << "time LS:" << totalTime / 100 << std::endl << std::endl;


    SingleLoopTimer SL_PS(20, new PerfectSleep);
    std::cout << "start PS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {
        SL_PS.StartLoop();
        SL_PS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end PS" << std::endl;
    std::cout << "time PS:" << totalTime / 100 << std::endl << std::endl;


    SingleLoopTimer SL_RS(20, new RobustSleep(PERIOD, TOLERANCE));
    std::cout << "start RS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {
        SL_RS.StartLoop();
        SL_RS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end RS" << std::endl;
    std::cout << "time RS:" << totalTime / 100 << std::endl << std::endl;
}
