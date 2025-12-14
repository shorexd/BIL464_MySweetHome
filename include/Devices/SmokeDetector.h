#ifndef SMOKEDETECTOR_H
#define SMOKEDETECTOR_H

#include "Logic/Observer.h"
#include "Device.h" // <--- EKLENDI
#include <string>
#include <vector>

class SmokeDetector : public ISubject, public Device {
private:
    std::vector<IObserver*> observers;

public:
    SmokeDetector();
    virtual ~SmokeDetector();

    // ISubject
    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify(const std::string& eventType);

    // Device
    void turnOn();
    void turnOff();
    Device* clone() const;

    // Ozel
    void detectSmoke();
    std::string getType() const; 
};

#endif