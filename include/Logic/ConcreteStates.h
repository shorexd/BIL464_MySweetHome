#ifndef CONCRETESTATES_H
#define CONCRETESTATES_H

#include "HomeState.h"

// --- Normal State ---
class NormalState : public HomeState {
public:
    void enterState(SystemController* context);
    void exitState(SystemController* context);
    void handle(SystemController* context);
    std::string getName() const;
    HomeState* clone() const;
    
    std::string getPerformance() const;
    std::string getFanSpeed() const;
    std::string getPowerUsage() const;
};

// --- High Performance State ---
class HighPerformanceState : public HomeState {
public:
    void enterState(SystemController* context);
    void exitState(SystemController* context);
    void handle(SystemController* context);
    std::string getName() const;
    HomeState* clone() const;

    std::string getPerformance() const;
    std::string getFanSpeed() const;
    std::string getPowerUsage() const;
};

// --- Low Power State ---
class LowPowerState : public HomeState {
public:
    void enterState(SystemController* context);
    void exitState(SystemController* context);
    void handle(SystemController* context);
    std::string getName() const;
    HomeState* clone() const;

    std::string getPerformance() const;
    std::string getFanSpeed() const;
    std::string getPowerUsage() const;
};

// --- Sleep State ---
class SleepState : public HomeState {
public:
    void enterState(SystemController* context);
    void exitState(SystemController* context);
    void handle(SystemController* context);
    std::string getName() const;
    HomeState* clone() const;

    std::string getPerformance() const;
    std::string getFanSpeed() const;
    std::string getPowerUsage() const;
};

#endif