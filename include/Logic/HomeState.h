#ifndef HOMESTATE_H
#define HOMESTATE_H

#include <string>

// Forward Declaration (Sistemin adini SystemController olarak biliyoruz)
class SystemController;

class HomeState {
public:
    virtual ~HomeState() {}
    
    // Context artik MSH degil SystemController
    virtual void enterState(SystemController* context) = 0;
    virtual void exitState(SystemController* context) = 0;
    virtual void handle(SystemController* context) = 0;
    virtual std::string getName() const = 0;

    // Getterlar
    virtual std::string getPerformance() const = 0;
    virtual std::string getFanSpeed() const = 0;
    virtual std::string getPowerUsage() const = 0;

    virtual HomeState* clone() const = 0;
};

#endif