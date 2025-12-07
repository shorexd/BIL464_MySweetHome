#ifndef HOMESTATE_H
#define HOMESTATE_H

#include <string>

class MSH;

class HomeState {
public:
    virtual ~HomeState() {}
    
    virtual void enterState(MSH* context) = 0;
    virtual void exitState(MSH* context) = 0;
    virtual void handle(MSH* context) = 0;
    virtual std::string getName() const = 0;

    // --- YENI EKLENEN OZELLIKLER ---
    virtual std::string getPerformance() const = 0; // Performans Durumu
    virtual std::string getFanSpeed() const = 0;    // Fan Hizi
    virtual std::string getPowerUsage() const = 0;  // Guc Tuketimi
    // -------------------------------

    virtual HomeState* clone() const = 0;
};

#endif