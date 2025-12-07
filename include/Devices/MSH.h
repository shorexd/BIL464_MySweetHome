#ifndef MSH_H
#define MSH_H

#include "HomeState.h"
#include "HomeStateMemento.h"
#include <string>

class MSH {
private:
    HomeState* currentState;

public:
    MSH();
    ~MSH();

    void changeState(HomeState* newState);
    void requestAction();
    std::string getStateName() const;

    // --- YENI GETTER FONKSIYONLARI ---
    std::string getPerformance() const { return currentState ? currentState->getPerformance() : "N/A"; }
    std::string getFanSpeed() const { return currentState ? currentState->getFanSpeed() : "N/A"; }
    std::string getPowerUsage() const { return currentState ? currentState->getPowerUsage() : "N/A"; }
    // ---------------------------------

    HomeStateMemento saveState();
    void restoreState(const HomeStateMemento& memento);
};

#endif