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
#define ITTERATIONS 100
#define LOOPTIME 20

int main()
{
    #pragma comment(lib, "winmm.lib") // for timeBeginPeriod
    timeBeginPeriod(PERIOD);

    SingleLoopTimer SL_TS(LOOPTIME, new ThreadSleep);
    std::cout << "start SL_TS" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        SL_TS.StartLoop();
        SL_TS.HandleLoop();
    }
    auto end = std::chrono::high_resolution_clock::now();
    double totalTime = (end - start).count() / 1e6;
    std::cout << "end SL_TS" << std::endl;
    std::cout << "time SL_TS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    SingleLoopTimer SL_LS(LOOPTIME, new LockSleep);
    std::cout << "start SL_LS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        SL_LS.StartLoop();
        SL_LS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end SL_LS" << std::endl;
    std::cout << "time SL_LS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    SingleLoopTimer SL_PS(LOOPTIME, new PerfectSleep);
    std::cout << "start SL_PS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        SL_PS.StartLoop();
        SL_PS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end SL_PS" << std::endl;
    std::cout << "time SL_PS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    SingleLoopTimer SL_RS(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE));
    std::cout << "start SL_RS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        SL_RS.StartLoop();
        SL_RS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end SL_RS" << std::endl;
    std::cout << "time SL_RS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    DoubleLoopTimer DL_TS(LOOPTIME, new ThreadSleep);
    std::cout << "start DL_TS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        DL_TS.StartLoop();
        DL_TS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end DL_TS" << std::endl;
    std::cout << "time DL_TS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    DoubleLoopTimer DL_LS(LOOPTIME, new LockSleep);
    std::cout << "start DL_LS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        DL_LS.StartLoop();
        DL_LS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end DL_LS" << std::endl;
    std::cout << "time DL_LS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    DoubleLoopTimer DL_PS(LOOPTIME, new PerfectSleep);
    std::cout << "start DL_PS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        DL_PS.StartLoop();
        DL_PS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end DL_PS" << std::endl;
    std::cout << "time DL_PS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    DoubleLoopTimer DL_RS(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE));
    std::cout << "start DL_RS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        DL_RS.StartLoop();
        DL_RS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end DL_RS" << std::endl;
    std::cout << "time DL_RS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    AllLoopTimerC ALC_TS(LOOPTIME, new ThreadSleep);
    std::cout << "start ALC_TS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        ALC_TS.StartLoop();
        ALC_TS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end ALC_TS" << std::endl;
    std::cout << "time ALC_TS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    AllLoopTimerC ALC_LS(LOOPTIME, new LockSleep);
    std::cout << "start ALC_LS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        ALC_LS.StartLoop();
        ALC_LS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end ALC_LS" << std::endl;
    std::cout << "time ALC_LS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    AllLoopTimerC ALC_PS(LOOPTIME, new PerfectSleep);
    std::cout << "start ALC_PS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        ALC_PS.StartLoop();
        ALC_PS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end ALC_PS" << std::endl;
    std::cout << "time ALC_PS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    AllLoopTimerC ALC_RS(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE));
    std::cout << "start ALC_RS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        ALC_RS.StartLoop();
        ALC_RS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end ALC_RS" << std::endl;
    std::cout << "time ALC_RS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    AllLoopTimerS ALS_TS(LOOPTIME, new ThreadSleep);
    std::cout << "start ALS_TS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        ALS_TS.StartLoop();
        ALS_TS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end ALS_TS" << std::endl;
    std::cout << "time ALS_TS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    AllLoopTimerS ALS_LS(LOOPTIME, new LockSleep);
    std::cout << "start ALS_LS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        ALS_LS.StartLoop();
        ALS_LS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end ALS_LS" << std::endl;
    std::cout << "time ALS_LS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    AllLoopTimerS ALS_PS(LOOPTIME, new PerfectSleep);
    std::cout << "start ALS_PS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        ALS_PS.StartLoop();
        ALS_PS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end ALS_PS" << std::endl;
    std::cout << "time ALS_PS:" << totalTime / ITTERATIONS << std::endl << std::endl;


    AllLoopTimerS ALS_RS(LOOPTIME, new RobustSleep(PERIOD, TOLERANCE));
    std::cout << "start ALS_RS" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITTERATIONS; i++)
    {
        ALS_RS.StartLoop();
        ALS_RS.HandleLoop();
    }
    end = std::chrono::high_resolution_clock::now();
    totalTime = (end - start).count() / 1e6;
    std::cout << "end ALS_RS" << std::endl;
    std::cout << "time ALS_RS:" << totalTime / ITTERATIONS << std::endl << std::endl;
}
